//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_CONCURRENT_STACK_INC__
# define __GLYNOS_CONCURRENT_STACK_INC__


namespace glynos {
namespace concurrent {
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

    bool try_push(const T &value) {

    }

    void push(const T &value) {

    }

};
} // namespace concurrent
} // namespace glynos


#endif // __GLYNOS_CONCURRENT_STACK_INC__
