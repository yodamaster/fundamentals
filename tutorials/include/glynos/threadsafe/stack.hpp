//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_THREADSAFE_STACK_INC__
# define __GLYNOS_THREADSAFE_STACK_INC__


# include <exception>
# include <thread>
# include <memory>
# include <glynos/stack.hpp>


namespace glynos {
namespace threadsafe {
class empty_stack : public std::runtime_error {
public:

    empty_stack() : std::runtime_error("Stack is empty.") {

    }
};


template <
    class T
    >
class stack {

    stack(const stack &other) = delete;
    stack &operator = (const stack &other) = delete;

public:

    stack() {

    }

    ~stack() {

    }

    void push(const T &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        stack_.push(value);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (stack_.empty()) {
            throw empty_stack();
        }

        std::shared_ptr<T> result(new T(stack_.top()));
        stack_.pop();
        return result;
    }

    unsigned int count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return stack_.count();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return stack_.empty();
    }

private:

    glynos::stack<T> stack_;
    mutable std::mutex mutex_;

};
} // namespace threadsafe
} // namespace glynos


#endif // __GLYNOS_THREADSAFE_STACK_INC__
