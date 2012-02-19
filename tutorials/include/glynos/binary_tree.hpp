//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_BINARY_TREE_INC__
# define __GLYNOS_BINARY_TREE_INC__


# include <algorithm>
# include <memory>
# include <glynos/binary_tree/node.hpp>


namespace glynos {
template <
    class Key,
    class Value,
    class Compare
    >
class binary_tree {

public:

    typedef Key key_type;
    typedef Value value_type;

    typedef binary_tree_node<Key, Value, Compare> node_type;

    binary_tree() {

    }

    binary_tree(const binary_tree &other) {
        if (!other.empty()) {
            root_.reset(new node_type(*other.root_));
        }
    }

# if !defined(BOOST_NO_RVALUE_REFERENCES)
    binary_tree(binary_tree &&other)
        : root_(other.root_) {
        other.root_.reset();
    }
# endif // !defined(BOOST_NO_RVALUE_REFERENCES)

    binary_tree &operator = (const binary_tree &other) {
        binary_tree(other).swap(*this);
        return *this;
    }

# if !defined(BOOST_NO_RVALUE_REFERENCES)
    binary_tree &operator = (binary_tree &&other) {
        binary_tree(other).swap(std::move(*this));
        return *this;
    }
# endif // !defined(BOOST_NO_RVALUE_REFERENCES)

    ~binary_tree() {

    }

    void swap(binary_tree &other) {
        std::swap(root_, other.root_);
    }

    bool insert(const Key &key, const Value &value) {
        auto node = find(key);
        if (node) {
            return false;
        }

		std::shared_ptr<node_type> new_node(new node_type(key, value, compare_));
        if (!empty()) {
            root_->insert(new_node);
        }
        else {
            root_ = new_node;
        }
        return true;
    }

    std::shared_ptr<node_type> find(const Key &key) {
        if (!empty()) {
            return root_->find(key);
        }
        return std::shared_ptr<node_type>();
    }

    void remove(const Key &key) {
        auto node = find(key);
        if (key) {
            if (!node->left) {
                transplant(node, node->right);
            }
            else if (!node->right) {
                transplant(node, node->left);
            }
            else {
                auto y = node->right->minimum();
                if (y->parent != node) {
                    transplant(y, y->right);
                    y->right = node->right;
                    y->right->parent = y;
                }
                transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
            }
        }
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

    unsigned int count() const {
        return root_? root_->count() : 0U;
    }

    unsigned int height() const {
        return root_? root_->height() : 0U;
    }

private:

    void transplant(std::shared_ptr<node_type> u,
                    std::shared_ptr<node_type> v) {
        if (!u->parent) {
            root_ = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v) {
            v->parent = u->parent;
        }
    }

    std::shared_ptr<node_type> root_;
    Compare compare_;

};
} // namespace glynos


#endif // __GLYNOS_BINARY_TREE_INC__
