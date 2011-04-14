//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_QUEUE_INC__
# define __GLYNOS_QUEUE_INC__


# include <glynos/list.hpp>


namespace glynos {
template <
    class T
    >
class queue {

public:

    void push(const T &value) {
        queue_.add_tail(value);
    }

    const T &head() const {
        assert(!empty());
        return *queue_.head()->value.get();
    }

    void pop() {
        queue_.remove_head();
    }

    unsigned int count() const {
        return queue_.count();
    }

    bool empty() const {
        return queue_.empty();
    }

private:

    list<T> queue_;

};
} // namespace glynos


#endif // __GLYNOS_QUEUE_INC__
