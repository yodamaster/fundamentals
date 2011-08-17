//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


// p 160, C++ concurrency in action


#ifndef __GLYNOS_THREADSAFE_HASH_TABLE_INC__
# define __GLYNOS_THREADSAFE_HASH_TABLE_INC__

# include <glynos/list.hpp>
# include <functional>


namespace glynos {
namespace threadsafe {
template <
    typename Key,
    typename Value,
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

        std::shared_ptr<entry> find(const Key &key) {
            for (auto node = data.head_node(); node; node = node->next) {
                if (node->key == key) {
                    return node;
                }
            }
            return std::shared_ptr<entry>();
        }

        std;:shared_ptr<Value> value_for(const Key &key) {
            std::unique_ptr<std::shared_mutex> lock(mutex_);
        }

    };

public:

    bool empty() const {
        return true;
    }

private:

    unsigned int hash_to_index(unsigned int hash) const {
        return hash % length_;
    }

    unsigned int length_;
    bucket_type *table_;
    Hash hash_fun_;

};
} // namespace threadsafe
} // namespace glynos


#endif // __GLYNOS_THREADSAFE_HASH_TABLE_INC__
