//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <memory>
#include <thread>


#ifndef __GLYNOS_CONCURRENT_QUEUE_INC__
# define __GLYNOS_CONCURRENT_QUEUE_INC__


namespace glynos {
namespace concurrent {
template <
    class T
    >
class queue {
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

        std::unique_ptr<node_type> next;
        std::shared_ptr<T> value;
    };

    queue() {

    }

    queue(const queue &) = delete;
    queue &operator = (const queue &) = delete;

    ~queue() {

    }

    std::unique_ptr<value_type> pop() {
        std::lock_guard<std::mutex> lock(head_monitor_);
        std::unique_ptr<value_type> node(std::move(head_));
        head_ = std::move(head_->next);
        return node;
    }

    void push(const T &value) {
        std::unique_ptr<node_type> new_node(new node_type(value));
        {
            std::lock_guard<std::mutex> lock(tail_monitor_);
            node_type *new_tail = new_node.get();
            tail_->next = std::move(new_node);
            tail_ = new_tail;
        }
        has_tail_.notify_one();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(head_monitor_);
        return !static_cast<bool>(head_);
    }

private:

    mutable std::mutex head_monitor_;
    std::unique_ptr<node_type> head_;
    mutable std::mutex tail_monitor_;
    node_type *tail_;
    std::condition_variable has_tail_;

};
} // namespace concurrent
} // namespace glynos


#endif // __GLYNOS_CONCURRENT_QUEUE_INC__
