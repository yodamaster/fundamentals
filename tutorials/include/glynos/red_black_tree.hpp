//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_RED_BLACK_TREE_INC__
# define __GLYNOS_RED_BLACK_TREE_INC__


# include <algorithm>
# include <memory>
# include <glynos/binary_tree/node.hpp>


namespace glynos {
template <
    class Key,
    class Value,
    class Compare
    >
class red_black_tree {

    enum Color { Red, Black };

public:

    typedef Key key_type;
    typedef Value value_type;

    class node_type : public binary_tree_node<Key, Value, Compare> {
    public:

        node_type(const Key &key, const Value &value, const Compare &compare)
            : binary_tree_node<Key, Value, Compare>(key, value, compare) {

        }

        ~node_type() {

        }

        Color color;
    };

    red_black_tree() {

    }

    red_black_tree(const red_black_tree &other) {
        if (!other.empty()) {
            root_.reset(new node_type(*other.root_));
        }
    }

    red_black_tree(red_black_tree &&other)
        : root_(other.root_) {
        other.root_.reset();
    }

    red_black_tree &operator = (const red_black_tree &other) {
        red_black_tree(other).swap(*this);
        return *this;
    }

    red_black_tree &operator = (red_black_tree &&other) {
        red_black_tree(other).swap(std::move(*this));
        return *this;
    }

    ~red_black_tree() {

    }

    void swap(red_black_tree &other) {
        std::swap(root_, other.root_);
    }

    bool insert(const Key &key, const Value &value) {
        root_.reset(new node_type(key, value, compare_));
        return true;
    }

    std::shared_ptr<node_type> find(const Key &key) {
        if (!empty()) {
            return root_->find(key);
        }
        return std::shared_ptr<node_type>();
    }

    void remove(const Key &key) {

    }

    std::shared_ptr<node_type> minimum() {
        if (!empty()) {
            return root_->minimum();
        }
        return std::shared_ptr<node_type>();
    }

    std::shared_ptr<node_type> maximum() {
        if (!empty()) {
            return root_->maximum();
        }
        return std::shared_ptr<node_type>();
    }

    template <
        class Func
        >
    void preorder_walk(const Func &func) {
        if (!empty()) {
            root_->preorder_walk(func);
        }
    }

    template <
        class Func
        >
    void inorder_walk(const Func &func) {
        if (!empty()) {
            root_->inorder_walk_2(func);
        }
    }

    template <
        class Func
        >
    void postorder_walk(const Func &func) {
        if (!empty()) {
            root_->postorder_walk(func);
        }
    }

    template <
        class Func
        >
    void levelorder_walk(const Func &func) {
        if (!empty()) {
            root_->levelorder_walk(func);
        }
    }

    template <
        class Func
        >
    void walk(const Func &func) {
        inorder_walk(func);
    }

    bool empty() const {
        return !static_cast<bool>(root_);
    }

    unsigned int count() {
        return root_? root_->count() : 0U;
    }

private:

    std::shared_ptr<node_type> root_;
    Compare compare_;

};
} // namespace glynos


#endif // __GLYNOS_RED_BLACK_TREE_INC__
