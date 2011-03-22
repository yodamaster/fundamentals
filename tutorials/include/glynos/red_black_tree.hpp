//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_RED_BLACK_TREE_INC__
# define __GLYNOS_RED_BLACK_TREE_INC__


# include <algorithm>
# include <memory>


namespace glynos {
template <
    class Key,
    class Value,
    class Pred
    >
class red_black_tree {

    class node_type
        : public std::enable_shared_from_this<node_type> {
        node_type(const Key &key, const Value &value, const Pred &pred)
            : pred(pred),
              key(key),
              value(value) {

        }

        ~node_type() {

        }

        std::shared_ptr<node_type> parent, left, right;
        const Pred &pred;
        const Key key;
        Value value;

        enum Color { Red, Black };
        Color color;


    };


};
} // namespace glynos


#endif // __GLYNOS_RED_BLACK_TREE_INC__
