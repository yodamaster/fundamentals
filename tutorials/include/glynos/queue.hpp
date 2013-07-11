//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_QUEUE_INC__
# define __GLYNOS_QUEUE_INC__


# include <glynos/list.hpp>


namespace glynos {
  //
  // \class queue glynos/queue.hpp
  // \brief A simple queue implementation.
  //
  template <
    class T
    >
  class queue {

  public:

    void push(T value) {
      queue_.add_tail(value);
    }

    T head() const {
      return queue_.head();
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
