#ifndef __GLYNOS_GENERIC_TREE_INC__
# define __GLYNOS_GENERIC_TREE_INC__


# include <glynos/list.hpp>
# include <glynos/stack.hpp>
# include <algorithm>
# include <memory>


namespace glynos {
template <
    class T
    >
class generic_tree {

public:

    typedef T value_type;

    struct node_type : public std::enable_shared_from_this<node_type> {
        node_type() {

        }

        node_type(const value_type &value) : value(new value_type(value)) {

        }

        template <
            class Func
            >
        void walk(Func &func) {
            stack<std::shared_ptr<node_type> > nodes;
            auto node = std::begin(children);

            while (true) {
                if (node != std::end(children)) {
                    nodes.push(node);
                    ++node;
                }
                else {
                    if (!nodes.empty()) {
                        node = nodes.top();
                        nodes.pop();
                        func(*node->value);
                        ++node;
                    }
                    else {
                        break;
                    }
                }
            }
        }

        void add_child(const value_type &value) {
            auto node(std::make_shared(new node_type(value)));
            children.add_tail(node);
        }

        std::shared_ptr<value_type> value;
        std::shared_ptr<node_type> parent;
        list<std::shared_ptr<node_type> > children;

    };

    generic_tree() : root_(new node_type) {

    }

    // void add_child(const T &value) {
    //     std::shared_ptr<node_type> node(new node_type(value));
    //     children_.add_tail(node);
    // }

    bool empty() const {
        return root_->children.empty();
    }

    std::shared_ptr<node_type> root() {
        return root_;
    }

    template <
        class Func
        >
    void walk(const Func &func) {
        root_->walk(func);
    }

private:

    std::shared_ptr<node_type> root_;

};
} // namespace glynos


#endif // __GLYNOS_GENERIC_TREE_INC__
