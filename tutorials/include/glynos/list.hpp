//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_LIST_INC__
# define __GLYNOS_LIST_INC__


# include <algorithm>
# include <memory>
# include <functional>


namespace glynos {
//
// \class list
//
template <
    class T
    >
class list {

public:

    typedef T value_type;

    //
    // \class node_type
    //
    class node_type {

# if !defined(BOOST_NO_DELETED_FUNCTIONS)
        node_type(const node_type &) = delete;
        node_type &operator = (const node_type &) = delete;
# endif // !defined(BOOST_NO_DELETED_FUNCTIONS)

    public:

        node_type(const value_type &value)
            : value(new value_type(value)) {

        }

        ~node_type() {

        }

        std::shared_ptr<node_type> prev, next;
        std::shared_ptr<value_type> value;

    };

    //
    // \brief Constructor.
    //
    list() {

    }

# if !defined(BOOST_NO_INITIALIZER_LISTS)
    //
    // \brief Initializer list constructor.
    //
    list(std::initializer_list<T> items) {
        using std::placeholders::_1;
        std::for_each(items.begin(), items.end(),
                      std::bind(&list<T>::add_tail, this, _1));
    }
# endif // !defined(BOOST_NO_INITIALIZER_LISTS)

    //
    // \brief Copy constructor.
    //
    list(const list &other) {
        if (!other.empty()) {
            head_.reset(new node_type(*other.head_->value));
            tail_ = head_;

            for (auto node = other.head_->next; node; node = node->next) {
                auto new_node(std::make_shared(new node_type(*node->value));
                tail_->next = new_node;
                new_node->prev = tail_;
                tail_ = new_node;
            }
        }
    }

# if !defined(BOOST_NO_RVALUE_REFERENCES)
    //
    // \brief Move constructor.
    //
    list(list &&other)
        : head_(other.head_),
          tail_(other.tail_) {
        other.head_.reset();
        other.tail_.reset();
    }
# endif // !defined(BOOST_NO_RVALUE_REFERENCES)

    //
    // \brief Assignment operator.
    //
    list &operator = (const list &other) {
        list(other).swap(*this);
        return *this;
    }

# if !defined(BOOST_NO_RVALUE_REFERENCES)
    //
    // \brief Move assignment operator.
    //
    list &operator = (list &&other) {
        list(std::move(other)).swap(*this);
        return *this;
    }
# endif // !defined(BOOST_NO_RVALUE_REFERENCES)

    //
    // \brief Destructor.
    //
    ~list() {

    }

    //
    // \brief Swaps this list with another.
    // \param other Another list.
    //
    void swap(list &other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
    }

    //
    // \brief Adds a value to the head of the list.
    // \param value The value to add at the head of the list.
    //
    void add_head(const T &value) {
        auto node(std::make_shared(new node_type(value)));
        if (head_) {
            head_->prev = node;
            node->next = head_;
        }
        head_ = node;
        if (!tail_) {
            tail_ = head_;
        }
    }

    //
    // \brief Removes a value from the head of the list.
    // Does nothing if the list is empty.
    //
    void remove_head() {
        if (head_) {
            auto new_head = head_->next;
            if (new_head) {
                new_head->prev.reset();
            }
            head_ = new_head;
            if (!head_) {
                tail_.reset();
            }
        }
    }

    //
    // \brief Returns a pointer to the head of the list.
    // Returns a null pointer if empty.
    //
    std::shared_ptr<node_type> head_node() {
        return head_;
    }

    //
    // \brief Returns a const pointer to the head of the list.
    // Returns a null pointer if empty.
    //
    std::shared_ptr<const node_type> head_node() const {
        return head_;
    }

    //
    // \brief Returns a reference to the head value.
    // \return The head value.
    // \pre !list.empty()
    //
    T &head() {
        assert(!empty());
        return *head_->value;
    }

    //
    // \brief Returns a const reference to the head value.
    // \return The head value.
    // \pre !list.empty()
    //
    const T &head() const {
        assert(!empty());
        return *head_->value;
    }

    //
    // \brief Adds a value to the tail of the list.
    // \param value A value to add to the tail.
    //
    void add_tail(const T &value) {
        auto node(std::make_shared(new node_type(value)));
        if (tail_) {
            tail_->next = node;
            node->prev = tail_;
        }
        tail_ = node;
        if (!head_) {
            head_ = tail_;
        }
    }

    //
    // \brief Removes a value from the tail of the list.
    // Does nothing of the list is empty.
    //
    void remove_tail() {
        if (tail_) {
            auto new_tail = tail_->prev;
            if (new_tail) {
                new_tail->next.reset();
            }
            tail_ = new_tail;
            if (!tail_) {
                head_.reset();
            }
        }
    }

    //
    // \brief Returns a pointer to the tail node.
    // \return The tail node or a null pointer of the list is empty.
    //
    std::shared_ptr<node_type> tail_node() {
        return tail_;
    }

    //
    // \brief Returns a pointer to the tail node.
    // \return The tail node or a null pointer of the list is empty.
    //
    std::shared_ptr<const node_type> tail_node() const {
        return tail_;
    }

    //
    // \brief Returns a reference to the value at the tail of the
    //        list.
    // \return The tail of the list.
    //
    T &tail() {
        assert(!empty());
        return *tail_->value;
    }

    //
    // \brief Returns a reference to the value at the tail of the
    //        list.
    // \return The tail of the list.
    //
    const T &tail() const {
        assert(!empty());
        return *tail_->value;
    }

    //
    // \brief Inserts a value after the node, if it exists in the
    //        list.
    //
    void insert_after(std::shared_ptr<node_type> node, const T &value) {
        auto new_node(std::make_shared(new node_type(value)));
        if (node->next) {
            new_node->next = node->next;
            node->next->prev = new_node;
            tail_ = new_node;
        }
        node->next = new_node;
        new_node->prev = node;
    }

    //
    // \brief Removes the node from the list.
    // \return A
    std::shared_ptr<node_type> remove(std::shared_ptr<node_type> node) {
        auto next = node->next;
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

    //
    // \brief Walks through every element in the list and applies the
    //        function object.
    //
    template <
        class Func
        >
    void walk(const Func &func) {
        for (auto node = head_; node; node = node->next) {
            func(*node->value);
        }
    }

    //
    // \brief Walks backwards through every element in the list and
    //        applies the function object.
    //
    template <
        class Func
        >
    void reverse_walk(const Func &func) {
        for (auto node = tail_; node; node = node->prev) {
            func(*node->value);
        }
    }

    //
    // \brief Sorts the list.
    //
    // This implementation uses merge sort and is O(N ln(N)).
    template <
        class Func
        >
    list sort(const Func &func) const {
        auto count_ = count();
        if (count_ <= 1) {
            return *this;
        }

        list left, right;
        auto middle = count_ >> 1;
        auto node = head_;

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

    //
    // \brief Finds the first element in the list such that
    //        func(element) returns \c true.
    //
    template <
        class Func
        >
    std::shared_ptr<const node_type> find(const Func &func) const {
        for (auto node = head_; node; node = node->next) {
            if (func(*node->value)) {
                return  node;
            }
        }
        return std::shared_ptr<const node_type>();
    }

    //
    // \brief
    //
    bool empty() const {
        return !head_;
    }

    //
    // Returns the number of elements in the list.
    //
    unsigned int count() const {
        unsigned int count = 0;
		//walk([&count](const T &) { ++count; });
        for (auto node = head_; node; node = node->next) {
            ++count;
        }
        return count;
    }

private:

    template <
        class Func
        >
    list &&merge(const list &left, const list &right, const Func &func) const {
        list result;
        auto left_node(left.head_node()), right_node(right.head_node());
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
        return std::move(result);
    }

    std::shared_ptr<node_type> head_, tail_;

};


//
// \brief Equality operator.
//
template <
    class T
    >
bool operator == (const list<T> &l1, const list<T> &l2) {
    auto n1 = l1.head_node(), n2 = l2.head_node();
    while (n1 && n2) {
        if (*n1->value != *n2->value) {
            break;
        }
        n1 = n1->next;
        n2 = n2->next;
    }
    return !n1 && !n2;
}

//
// \brief Inequality operator.
//
template <
    class T
    >
bool operator != (const list<T> &l1, const list<T> &l2) {
    return !(l1 == l2);
}
} // namespace glynos


#endif // __GLYNOS_LIST_INC__
