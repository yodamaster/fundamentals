/*
 * Based on http://norvig.com/lispy.html
 */

#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <tr1/memory>
#include <utility>

namespace Lispic {

  using namespace std;                                           // Standards, gotta love 'em
  using namespace tr1;                                           // Can't have enough shared_ptr's

  /* ------------------------- */

  struct Value {
    typedef shared_ptr<Value> p;                                 // Pointer to value
    enum    t { STRING, SYMBOL, INT, LIST, LAMBDA };             // Reify value type
    virtual t type() = 0;                                        // Access value type
    virtual operator bool() = 0;                                 // Access value as Boolean
    virtual string to_string() = 0;                              // Access value as string
  };

  /* ------------------------- */

  class String : public Value {
  public:
    typedef shared_ptr<String> p;
    struct less {                                                // "Functor" used to create maps of Strings
      bool operator()(const String::p& l, const String::p& r) const { return l->_s < r->_s; }
    };
    String(string s) : _s(s) { }
    Value::t type() { return STRING; }
    operator bool() { return !_s.empty(); }
    string to_string() { return _s; }
  protected:
    string _s;
  };

  /* ------------------------- */

  class Symbol : public String {                                 // A Symbol is a specialized String
  public:
    typedef shared_ptr<Symbol> p;
    Symbol(string s) : String(s) { }
    Value::t type() { return SYMBOL; }
    static p create(string s) { return p(new Symbol(s)); }       // Handy function to create a Symbol
  };

  /* ------------------------- */

  class Int : public Value {
  public:
    typedef shared_ptr<Int> p;
    Int(long i) : _i(i) { }
    Value::t type() { return INT; }
    operator bool() { return _i == 0; }
    long to_int() { return _i; }
    string to_string() { ostringstream oss; oss << _i; return oss.str(); }
  private:
    long _i;
  };

  /* ------------------------- */

  class List : public Value {
  public:
    typedef shared_ptr<List> p;
    static p create() { return p(new List()); }
    static p create(list<Value::p> l) { return p(new List(l)); }
    static p create(list<Value::p>::iterator b, list<Value::p>::iterator e) { return p(new List(b,e)); }
    Value::t type() { return LIST; }
    operator bool() { return !_l.empty(); }
    list<Value::p>& to_list() { return _l; }
    string to_string() {
      ostringstream oss;
      oss << "(";
      for (list<Value::p>::iterator i = _l.begin(); i != _l.end(); ++i) { oss << (*i)->to_string() << " "; }
      oss << ")";
      return oss.str();
    }
  private:
    list<Value::p> _l;
    List() { }
    List(list<Value::p> l) : _l(l) { }
    List(list<Value::p>::iterator b, list<Value::p>::iterator e) : _l(b,e) { }
  };

  /* ------------------------- */

  class Environment {
  public:
    typedef shared_ptr<Environment> p;
    typedef map<Symbol::p,Value::p,Symbol::less> env_t;
   
    static p create() { return Lispic::Environment::p(new Lispic::Environment()); }
    static p create(p outer) { return Lispic::Environment::p(new Lispic::Environment(outer)); }

    virtual void update(Symbol::p s, Value::p v) { _e.insert( make_pair(s,v) ); }
    virtual env_t& find(Symbol::p s) { return _e.count(s) > 0 ? _e : _outer->find(s); }

  private:
    env_t _e;
    p _outer;

    Environment() { }
    Environment(p outer) : _outer(outer) { }
  };

  /* ------------------------- */

  Value::p eval(Value::p x, Environment::p env);

  class Lambda : public Value {
  public:
    typedef shared_ptr<Lambda> p;
    static p create(List::p params, List::p exp) { return p(new Lambda(params,exp)); }
    Value::t type() { return LAMBDA; }
    operator bool() { return true; }
    string to_string() { return "LAMBDA"; }

    virtual Value::p operator()(List::p args, Environment::p outer) {
      return eval(_e, create_env(outer, _p->to_list(), args->to_list()));
    }

  private:
    List::p _p;
    List::p _e;
  protected:
    Lambda(List::p p, List::p e) : _p(p), _e(e) { }

    Environment::p create_env(Environment::p outer, list<Value::p> &params, list<Value::p> &args) {
      list<Value::p>::iterator p_begin = params.begin();
      list<Value::p>::iterator p_end = params.end();
      list<Value::p>::iterator a_begin = args.begin();
      list<Value::p>::iterator a_end = args.end();
      Environment::p env = Environment::create(outer);
      for (; p_begin != p_end && a_begin != a_end; p_begin++, a_begin++) {
        Symbol::p symb = dynamic_pointer_cast<Symbol>(*p_begin);
        env->update(symb, *a_begin);
      }
      return env;
    }
  };

  struct Builtin : public Lambda {
    virtual Value::p operator()(List::p args, Environment::p outer) = 0;
    Builtin(List::p p) : Lambda(p,List::p()) { }
  };

  struct Plus : public Builtin {
    Plus(List::p p) : Builtin(p) { }
    Value::p operator()(List::p args, Environment::p outer) {
      list<Value::p>::iterator end = args->to_list().end();
      long sum = 0;
      for (list<Value::p>::iterator i = args->to_list().begin(); i != end; ++i) {
        sum += dynamic_pointer_cast<Int>(*i)->to_int();
      }
      return Int::p(new Int(sum));
    }
  };

  struct Print : public Builtin {
    Print(List::p p) : Builtin(p) { }
    Value::p operator()(List::p args, Environment::p outer) {
      list<Value::p>::iterator it = args->to_list().begin();
      list<Value::p>::iterator end = args->to_list().end();
      Value::p value;
      for (; it != end; ++it) {
        value = *it;
        cout << value->to_string() << endl;
      }
      return value;
    }
  };

  /* ------------------------- */

  class NullEnvironment : Environment {
  public:
    class Ex { };
    virtual void update(Symbol::p& s, Value::p& v) { }
    virtual env_t& find(Symbol::p s) {
      std::cerr << "Unknown symbol: " << s->to_string() << std::endl;
      throw Ex();
    }
  };

  /* ------------------------- */

  Value::p eval(Value::p x, Environment::p env) {
    if (x->type() == Value::SYMBOL) {                            // Look up the value
      Symbol::p x1 = dynamic_pointer_cast<Symbol>(x);
      return env->find(x1)[x1];
    } else if (x->type() != Value::LIST) {                       // Everything else scalar is self-evaluating
      return x;
    } else {
      List::p l = dynamic_pointer_cast<List>(x);                 // This is where it gets exciting
      list<Value::p> repr = l->to_list();
      if (repr.size() > 0 && repr.front()->type() == Value::SYMBOL) {
        Symbol::p symbol = dynamic_pointer_cast<Symbol>(repr.front());
        list<Value::p>::iterator it = ++(repr.begin());          // The second element, needed by most branches
        list<Value::p>::iterator end = repr.end();               // The end of the list
        if ((symbol->to_string()) == "quote") {                  // quote: Return the rest of the list
          return List::create(++it, end);
        } else if ((symbol->to_string()) == "if") {              // if: Yeah, like this is going to work
          if (!(*eval(*it++, env))) { ++it; }
          return eval(*it, env);
        } else if ((symbol->to_string()) == "set!") {            // set!: Life does not get worse if I remove this
          Symbol::p var = dynamic_pointer_cast<Symbol>( eval(*it++, env) );
          Value::p val = eval(*it++, env);
          env->find(var)[var] = val;
          return val;
        } else if ((symbol->to_string()) == "define") {          // define: Hey, Mickey! You're so defined...
          Symbol::p var = dynamic_pointer_cast<Symbol>(*it++);   // Yeah, that's not even funny to me
          Value::p val = eval(*it++, env);
          env->update(var, val);
          return val;
        } else if ((symbol->to_string()) == "lambda") {          // lambda: first element is the parameters, next is the body
          List::p pars = dynamic_pointer_cast<List>(*it++);
          List::p body = dynamic_pointer_cast<List>(*it);
          return Lambda::create(pars, body);
        } else if ((symbol->to_string()) == "begin") {           // begin: evaluate 'em all and let McCarthy sort 'em out
          Value::p value;
          for (; it != end; ++it) { value = eval(*it, env); }
          return value;
        } else {                                                 // application: this is where it gets really exciting
          list<Value::p>::iterator it = repr.begin();            // The beginning of the list
          list<Value::p> evaluated;
          for (; it != end; ++it) { evaluated.push_back( eval(*it, env) ); }
          {
            Lambda::p lambda = dynamic_pointer_cast<Lambda>(evaluated.front());
            List::p args = List::create(++(evaluated.begin()), evaluated.end());
            return (*lambda)(args, env);
          }
        }
      }
    }
  }

  /* ------------------------- */

  void replace(string &s, string from, string to) {
    int idx = 0;
    int next;
    while ((next = s.find(from, idx)) != string::npos) {
      s.replace(next, from.size(), to);
      idx = next + to.size(); 
    }
  }

  list<string> tokenize(string s) {
    replace(s, "(", " ( ");
    replace(s, ")", " ) ");
    istringstream iss(s);
    list<string> result;
    result.insert(result.end(), istream_iterator<string>(iss), istream_iterator<string>());
    return result;
  }

  Value::p atom(string token) {
    istringstream oss(token);
    long l;
    if (oss >> l) { return Int::p(new Int(l)); } else { return Symbol::p(new Symbol(token)); }
  }

  Value::p read_from(list<string> &tokens) {
    if (tokens.size() <= 0) { /* error */ }
    string token = tokens.front();
    tokens.pop_front();
    if (token == "(") {
      list<Value::p> lst;
      while (tokens.front() != ")") {
        lst.push_back( read_from(tokens) );
      }
      tokens.pop_front();
      return List::create(lst);
    } else if (token == ")") { /* error */
    } else {
      return atom(token);
    }
  }

  /* ------------------------- */

  Environment::p global_env() {
    Environment::p global = Environment::create();
    global->update( Symbol::create("+"), Lambda::p(new Plus(List::create())) );
    global->update( Symbol::create("print"), Lambda::p(new Print(List::create())) );
    return global;
  }

  /* ------------------------- */

};

int
main(int argc, char *argv[]) {
  Lispic::Environment::p global = Lispic::global_env();
  std::list<std::string> tokens = Lispic::tokenize(
    "(begin"
    "  (print (+ 2 3))"
    "  (define double (lambda (x) (+ x x)))"
    "  (print (+ 3 3) (double 4))"
    ")"
  );
  std::cout << Lispic::eval(Lispic::read_from(tokens), global)->to_string() << std::endl;
  return 0;
}
