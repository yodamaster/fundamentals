//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_LIST_INC__
# define __GLYNOS_LIST_INC__


# include <algorithm>
# include <memory>


namespace glynos {
/**
 *
 */
template <
    class T
    >
class list {

public:

    typedef T value_type;

    struct node_type {

        node_type(const node_type &) = delete;
        node_type &operator = (const node_type &) = delete;

        node_type(const value_type &value)
            : value(new value_type(value)) {

        }

        ~node_type() {

        }

        std::shared_ptr<node_type> prev, next;
        std::shared_ptr<value_type> value;

    };

    list() {

    }

    list(const list &other) {
        if (!other.empty()) {
            head_.reset(new node_type(*other.head_->value));
            tail_ = head_;

            for (std::shared_ptr<node_type> node = other.head_->next;
                 node;
                 node = node->next) {
                std::shared_ptr<node_type> new_node(new node_type(*node->value));
                tail_->next = new_node;
                new_node->prev = tail_;
                tail_ = new_node;
            }
        }
    }

    list(list &&other)
        : head_(other.head_),
          tail_(other.tail_) {
        other.head_.reset();
        other.tail_.reset();
    }

    list &operator = (const list &other) {
        list(other).swap(*this);
        return *this;
    }

    list &operator = (list &&other) {
        list(std::move(other)).swap(*this);
        return *this;
    }

    ~list() {

    }

    void swap(list &other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
    }

    void add_head(const T &value) {
        std::shared_ptr<node_type> node(new node_type(value));
        if (head_) {
            head_->prev = node;
            node->next = head_;
        }
        head_ = node;
        if (!tail_) {
            tail_ = head_;
        }
    }

    void remove_head() {
        if (head_) {
            std::shared_ptr<node_type> new_head = head_->next;
            if (new_head) {
                new_head->prev.reset();
            }
            head_ = new_head;
            if (!head_) {
                tail_.reset();
            }
        }
    }

    std::shared_ptr<node_type> head() {
        return head_;
    }

    std::shared_ptr<const node_type> head() const {
        return head_;
    }

    void add_tail(const T &value) {
        std::shared_ptr<node_type> node(new node_type(value));
        if (tail_) {
            tail_->next = node;
            node->prev = tail_;
        }
        tail_ = node;
        if (!head_) {
            head_ = tail_;
        }
    }

    void remove_tail() {
        if (tail_) {
            std::shared_ptr<node_type> new_tail = tail_->prev;
            if (new_tail) {
                new_tail->next.reset();
            }
            tail_ = new_tail;
            if (!tail_) {
                head_.reset();
            }
        }
    }

    std::shared_ptr<node_type> tail() {
        return tail_;
    }

    std::shared_ptr<const node_type> tail() const {
        return tail_;
    }

    void insert_after(std::shared_ptr<node_type> node, const T &value) {
        std::shared_ptr<node_type> new_node(new node_type(value));
        if (node->next) {
            new_node->next = node->next;
            node->next->prev = new_node;
            tail_ = new_node;
        }
        node->next = new_node;
        new_node->prev = node;
    }

    std::shared_ptr<node_type> remove(std::shared_ptr<node_type> node) {
        std::shared_ptr<node_type> next = node->next;
        if (node->prev) {
            node->prev->next = next;
        }
        else {
            head_ = next;
        }
        if (next) {
            next->prev = node->prev;
        }
        else {
            tail_ = node->prev;
        }
        return next;
    }

    template <
        class Func
        >
    void walk(const Func &func) {
        for (std::shared_ptr<node_type> node = head_; node; node = node->next) {
            func(*node->value);
        }
    }

    template <
        class Func
        >
    void reverse_walk(const Func &func) {
        for (std::shared_ptr<node_type> node = tail_; node; node = node->prev) {
            func(*node->value);
        }
    }

    template <
        class Func
        >
    list sort(const Func &func) const {
        unsigned int count_ = count();
        if (count_ <= 1) {
            return *this;
        }

        list left, right;
        unsigned int middle = count_ >> 1;
        std::shared_ptr<const node_type> node = head_;

        for (unsigned int i = 0; i < middle; ++i) {
            left.add_tail(*node->value);
            node = node->next;
        }

        for (unsigned int i = middle; i < count_; ++i) {
            right.add_tail(*node->value);
            node = node->next;
        }

        // TODO make this non-recursive
        return merge(left.sort(func), right.sort(func), func);
    }

    template <
        class Func
        >
    std::shared_ptr<const node_type> find(const Func &func) const {
        for (std::shared_ptr<node_type> node = head_;
             node;
             node = node->next) {
            if (func(*node->value)) {
                return  node;
            }
        }
        return std::shared_ptr<const node_type>();
    }

    bool empty() const {
        return !head_;
    }

    unsigned int count() const {
        unsigned int count = 0;
        for (std::shared_ptr<node_type> node = head_;
             node;
             node = node->next) {
            ++count;
        }
        return count;
    }

private:

    template <
        class Func
        >
    list merge(const list &left, const list &right, const Func &func) const {
        list result;
        std::shared_ptr<const node_type>
            left_node(left.head()), right_node(right.head());
        while (left_node || right_node) {
            if (left_node && right_node) {
                if (func(*left_node->value, *right_node->value)) {
                    result.add_tail(*left_node->value);
                    left_node = left_node->next;
                }
                else {
                    result.add_tail(*right_node->value);
                    right_node = right_node->next;
                }
            }
            else if (left_node) {
                result.add_tail(*left_node->value);
                left_node = left_node->next;
            }
            else if (right_node) {
                result.add_tail(*right_node->value);
                right_node = right_node->next;
            }
        }
        return result;
    }

    std::shared_ptr<node_type> head_, tail_;

};


template <
    class T
    >
bool operator == (const list<T> &l1, const list<T> &l2) {
    if (l1.count() != l2.count()) {
        return false;
    }

    std::shared_ptr<const typename list<T>::node_type> n1, n2;
    for (n1 = l1.head(), n2 = l2.head(); n1; n1 = n1->next, n2 = n2->next) {
        if (*n1->value != *n2->value) {
            return false;
        }
    }
    return true;
}

template <
    class T
    >
bool operator != (const list<T> &l1, const list<T> &l2) {
    return !(l1 == l2);
}
} // namespace glynos


#endif // __GLYNOS_LIST_INC__
