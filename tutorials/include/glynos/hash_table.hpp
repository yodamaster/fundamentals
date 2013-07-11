//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_HASH_TABLE_INC__
# define __GLYNOS_HASH_TABLE_INC__


# include "glynos/list.hpp"
# include <memory>
# include <functional>
# include <cstddef>
# include <cstring>


namespace glynos {
  template <
    class Key,
    class Value,
    typename Hash = std::hash<Key>
    >
  class hash_table {

    struct entry {

      entry(const Key &key, const Value &value, unsigned int hash)
	: key(new Key(key)), value(new Value(value)), hash(hash) {

      }

      ~entry() {

      }

      std::shared_ptr<const Key> key;
      std::shared_ptr<Value> value;
      unsigned int hash;

    };

    struct bucket_type {
      list<std::shared_ptr<entry> > data;
    };

  public:

    explicit hash_table(unsigned int min_size = 100,
                        const Hash &hash = Hash())
      : length_(min_size),
	table_(new bucket_type[length_]),
	hash_fun_(hash) {

    }

    hash_table(const hash_table &other)
      : length_(other.length_),
	table_(new bucket_type[length_]),
	hash_fun_(other.hash_fun_) {
      for (unsigned int i = 0; i < length_; ++i) {
	table_[i] = other.table_[i];
      }
    }

    hash_table &operator = (const hash_table &other) {
      hash_table(other).swap(*this);
      return *this;
    }

    ~hash_table() {
      delete [] table_;
    }

    void swap(hash_table &other) {
      std::swap(length_, other.length_);
      std::swap(table_, other.table_);
      std::swap(hash_fun_, other.hash_fun_);
    }

    bool insert(const Key &key, const Value &value) {
      auto hash = hash_fun_(key);
      auto index = hash_to_index(hash);
      for (auto node = table_[index].data.head_node(); node; node = node->next) {
	if (((*node->value)->hash == hash) &&
	    (*(*node->value)->key == key)) {
	  return false;
	}
      }
      std::shared_ptr<entry> e(new entry(key, value, hash));
      table_[index].data.add_tail(e);
      return true;
    }

    std::shared_ptr<const Value> find(const Key &key) const {
      auto hash = hash_fun_(key);
      auto index = hash_to_index(hash);
      std::shared_ptr<const Value> result;
      for (auto node = table_[index].data.head_node(); node; node = node->next) {
	if (((*node->value)->hash == hash) &&
	    (*(*node->value)->key == key)) {
	  result = (*node->value)->value;
	  break;
	}
      }
      return result;
    }

    void remove(const Key &key) {
      auto hash = hash_fun_(key);
      auto index = hash_to_index(hash);
      for (auto node = table_[index].data.head_node(); node; node = node->next) {
	if (((*node->value)->hash == hash) &&
	    (*(*node->value)->key == key)) {
	  table_[index].data.remove(node);
	  return;
	}
      }
    }

    template <
      class Func
      >
    void walk(const Func &func) {
      for (unsigned int i = 0; i < length_; ++i) {
	for (auto node = table_[i].data.head_node(); node; node = node->next) {
	  func(*(*node->value)->key, *(*node->value)->value);
	}
      }
    }

    unsigned int count() const {
      unsigned int count = 0;
      for (unsigned int i = 0; i < length_; ++i) {
	count += table_[i].data.count();
      }
      return count;
    }

    bool empty() const {
      return count() == 0;
    }

  private:

    unsigned int hash_to_index(unsigned int hash) const {
      return hash % length_;
    }

    unsigned int length_;
    bucket_type *table_;
    Hash hash_fun_;

  };
} // namespace glynos


#endif // __GLYNOS_HASH_TABLE_INC__
