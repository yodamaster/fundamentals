//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_BINARY_TREE_INC__
# define __GLYNOS_BINARY_TREE_INC__


# include <algorithm>
# include <memory>
# include <glynos/queue.hpp>
# include <glynos/stack.hpp>


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

    class node_type
        : public std::enable_shared_from_this<node_type> {

    public:

        node_type(const Key &key, const Value &value, const Compare &compare)
            : compare(compare),
              key(new Key(key)),
              value(new Value(value)) {

        }

        node_type(const node_type &other) {
            queue<std::shared_ptr<node_type> > nodes;
            nodes.push(other.shared_from_this());
            while (!nodes.empty()) {
                std::shared_ptr<node_type> node = nodes.front();
                // ...

                nodes.pop();
                if (node->left) {
                    nodes.push(node->left);
                }
                if (node->right) {
                    nodes.push(node->right);
                }
            }
            return;

        }

        node_type &operator = (const node_type &other) {
            node_type(other).swap(*this);
            return *this;
        }

        ~node_type() {

        }

        void insert(std::shared_ptr<node_type> node) {
            std::shared_ptr<node_type> x = this->shared_from_this(), y;
            while (x) {
                y = x;
                if (compare(*node->key, *x->key)) {
                    x = x->left;
                }
                else {
                    x = x->right;
                }
            }

            node->parent = y;
            if (y) {
                if (compare(*node->key, *y->key)) {
                    y->left = node;
                }
                else {
                    y->right = node;
                }
            }
        }

        std::shared_ptr<node_type> find(const Key &key) {
            std::shared_ptr<node_type> node = this->shared_from_this();
            while (node && (key != *node->key)) {
                if (compare(key, *node->key)) {
                    node = node->left;
                }
                else {
                    node = node->right;
                }
            }
            return node;
        }

        // void remove(const Key &key) {
        //     std::shared_ptr<node_type> node = find(key);
        //     if (node) {
        //         // if it's a leaf, just remove it
        //         if (!node->left && !node->right) {
        //             if (node->shared_from_this() == node->parent->left) {
        //                 node->parent->left.reset();
        //             }
        //             else if (node->shared_from_this() == node->parent->right) {
        //                 node->parent->right.reset();
        //             }
        //         }
        //         else if (node->left && node->left) {
        //
        //         }
        //         else if (node->left) {
        //             if (node->shared_from_this() == node->parent->left) {
        //                 node->parent->left = node->left;
        //             }
        //             else if (node->shared_from_this() == node->parent->right) {
        //                 node->parent->right = node->left;
        //             }
        //         }
        //         else if (node->right) {
        //             // std;:shared_ptr<node_type> tmp = node;
        //             // while (tmp->right) {
        //             //     node
        //             // }
        //         }
        //     }
        // }

        std::shared_ptr<node_type> minimum() {
            std::shared_ptr<node_type> node = this->shared_from_this();
            while (node->left) {
                node = node->left;
            }
            return node;
        }

        std::shared_ptr<node_type> maximum() {
            std::shared_ptr<node_type> node = this->shared_from_this();
            while (node->right) {
                node = node->right;
            }
            return node;
        }

        template <
            class Func
            >
        void preorder_walk(const Func &func) {
            // todo - make this non-recursive
            func(*key, *value);
            if (left) {
                left->preorder_walk(func);
            }
            if (right) {
                right->preorder_walk(func);
            }
        }

        template <
            class Func
            >
        void inorder_walk_1(const Func &func) {
            // this implementation doesn't use a stack, or recursion,
            // but does modify the original structure.
            std::shared_ptr<node_type> node = this->shared_from_this(), pre;
            while (node) {
                if (!node->left) {
                    func(*node->key, *node->value);
                    node = node->right;
                }
                else {
                    pre = node->left;
                    while (pre->right && (pre->right != node)) {
                        pre = pre->right;
                    }

                    if (!pre->right) {
                        pre->right = node;
                        node = node->left;
                    }
                    else {
                        pre->right.reset();
                        func(*node->key, *node->value);
                        node = node->right;
                    }
                }
            }
        }

        template <
            class Func
            >
        void inorder_walk_2(const Func &func) {
            // uses a stack, doesn't modify structure
            stack<std::shared_ptr<node_type> > nodes;
            std::shared_ptr<node_type> node = this->shared_from_this();

            while (true) {
                if (node) {
                    nodes.push(node);
                    node = node->left;
                }
                else {
                    if (!nodes.empty()) {
                        node = nodes.top();
                        nodes.pop();
                        func(*node->key, *node->value);
                        node = node->right;
                    }
                    else {
                        break;
                    }
                }
            }
        }

        template <
            class Func
            >
        void postorder_walk(const Func &func) {
            // todo - make this non-recursive
            if (left) {
                left->postorder_walk(func);
            }
            if (right) {
                right->postorder_walk(func);
            }
            func(*key, *value);
        }

        template <
            class Func
            >
        void levelorder_walk(const Func &func) {
            queue<std::shared_ptr<node_type> > nodes;
            nodes.push(this->shared_from_this());
            while (!nodes.empty()) {
                std::shared_ptr<node_type> node = nodes.front();
                nodes.pop();

                func(*node->key, *node->value);
                if (node->left) {
                    nodes.push(node->left);
                }
                if (node->right) {
                    nodes.push(node->right);
                }
            }
        }

        unsigned int count() const {
            unsigned int count = 0;
            queue<std::shared_ptr<const node_type> > nodes;
            nodes.push(this->shared_from_this());
            while (!nodes.empty()) {
                std::shared_ptr<const node_type> node = nodes.front();
                nodes.pop();
                ++count;
                if (node->left) {
                    nodes.push(node->left);
                }
                if (node->right) {
                    nodes.push(node->right);
                }
            }
            return count;
        }

        std::shared_ptr<node_type> parent, left, right;
        const Compare &compare;
        std::shared_ptr<const Key> key;
        std::shared_ptr<Value> value;

    };

    binary_tree() {

    }

    binary_tree(const binary_tree &other) {
        if (!other.empty()) {
            root_.reset(new node_type(*other.root_));
        }
    }

    binary_tree(binary_tree &&other)
        : root_(other.root_) {
        other.root_.reset();
    }

    binary_tree &operator = (const binary_tree &other) {
        binary_tree(other).swap(*this);
        return *this;
    }

    binary_tree &operator = (binary_tree &&other) {
        binary_tree(other).swap(std::move(*this));
        return *this;
    }

    ~binary_tree() {

    }

    void swap(binary_tree &other) {
        std::swap(root_, other.root_);
    }

    bool insert(const Key &key, const Value &value) {
        std::shared_ptr<const node_type> node = find(key);
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
        std::shared_ptr<node_type> node = find(key);
        if (key) {
            if (!node->left) {
                transplant(node, node->right);
            }
            else if (!node->right) {
                transplant(node, node->left);
            }
            else {
                std::shared_ptr<node_type> y = node->right->minimum();
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

    unsigned int count() {
        return root_? root_->count() : 0;
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
