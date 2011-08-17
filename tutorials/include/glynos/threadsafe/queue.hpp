//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <memory>
#include <thread>
#include <exception>
#include <glynos/queue.hpp>


#ifndef __GLYNOS_THREADSAFE_QUEUE_INC__
# define __GLYNOS_THREADSAFE_QUEUE_INC__


namespace glynos {
namespace threadsafe {
class empty_queue : public std::runtime_error {
public:

    empty_queue() : std::runtime_error("Queue is empty.") {

    }

};


template <
    class T
    >
class queue {
public:

    queue() {

    }

    queue(const queue &) = delete;
    queue &operator = (const queue &) = delete;

    ~queue() {

    }

    void push(const T &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            throw empty_queue();
        }

        std::shared_ptr<T> result(new T(queue_.head()));
        queue_.pop();
        return result;
    }

    unsigned int count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.count();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:

    glynos::queue<T> queue_;
    mutable std::mutex mutex_;

};
} // namespace threadsafe
} // namespace glynos


#endif // __GLYNOS_THREADSAFE_QUEUE_INC__
