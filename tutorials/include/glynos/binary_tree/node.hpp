//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_BINARY_TREE_NODE_INC__
# define __GLYNOS_BINARY_TREE_NODE_INC__


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
class binary_tree_node
    : public std::enable_shared_from_this<binary_tree_node<Key, Value, Compare> > {

public:

    binary_tree_node(const Key &key, const Value &value, const Compare &compare)
        : compare(compare),
          key(new Key(key)),
          value(new Value(value)) {

    }

    binary_tree_node(const binary_tree_node &other) {
        queue<std::shared_ptr<binary_tree_node> > nodes;
        nodes.push(other.shared_from_this());
        while (!nodes.empty()) {
            std::shared_ptr<binary_tree_node> node = nodes.front();
            nodes.pop();

            // ...
            // insert?

            if (node->left) {
                nodes.push(node->left);
            }
            if (node->right) {
                nodes.push(node->right);
            }
        }
        return;

    }

    binary_tree_node &operator = (const binary_tree_node &other) {
        binary_tree_node(other).swap(*this);
        return *this;
    }

    ~binary_tree_node() {

    }

    void insert(std::shared_ptr<binary_tree_node> node) {
        std::shared_ptr<binary_tree_node> x = this->shared_from_this(), y;
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

    std::shared_ptr<binary_tree_node> find(const Key &key) {
        std::shared_ptr<binary_tree_node> node = this->shared_from_this();
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

    std::shared_ptr<binary_tree_node> minimum() {
        std::shared_ptr<binary_tree_node> node = this->shared_from_this();
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    std::shared_ptr<binary_tree_node> maximum() {
        std::shared_ptr<binary_tree_node> node = this->shared_from_this();
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
        std::shared_ptr<binary_tree_node> node = this->shared_from_this(), pre;
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
        stack<std::shared_ptr<binary_tree_node> > nodes;
        std::shared_ptr<binary_tree_node> node = this->shared_from_this();

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
        queue<std::shared_ptr<binary_tree_node> > nodes;
        nodes.push(this->shared_from_this());
        while (!nodes.empty()) {
            std::shared_ptr<binary_tree_node> node = nodes.front();
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
        queue<std::shared_ptr<const binary_tree_node> > nodes;
        nodes.push(this->shared_from_this());
        while (!nodes.empty()) {
            std::shared_ptr<const binary_tree_node> node = nodes.front();
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

    std::shared_ptr<binary_tree_node> parent, left, right;
    const Compare &compare;
    std::shared_ptr<const Key> key;
    std::shared_ptr<Value> value;

};
} // namespace glynos


#endif // __GLYNOS_BINARY_TREE_NODE_INC__
