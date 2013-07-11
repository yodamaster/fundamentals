//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_STACK_INC__
# define __GLYNOS_STACK_INC__


# include <glynos/list.hpp>


namespace glynos {
  //
  // \class stack glynos.stack.hpp
  // \brief A simple stack implementation.
  //
  template <
    class T
    >
  class stack {

  public:

    void push(const T &value) {
      stack_.add_tail(value);
    }

    const T &top() const {
      return stack_.tail();
    }

    void pop() {
      stack_.remove_tail();
    }

    unsigned int count() const {
      return stack_.count();
    }

    bool empty() const {
      return stack_.empty();
    }

  private:

    list<T> stack_;

  };
} // namespace glynos


#endif // __GLYNOS_STACK_INC__
