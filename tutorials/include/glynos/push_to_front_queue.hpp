//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_PUSH_TO_FRONT_QUEUE_INC__
# define __GLYNOS_PUSH_TO_FRONT_QUEUE_INC__


# include <glynos/list.hpp>


namespace glynos {
  template <
    class T
    >
  class push_to_front_queue {

  public:

    void push(T value) {
      queue_.add_tail(value);
    }

    const T &front() const {
      assert(!empty());
      return *queue_.head()->value.get();
    }

    template <
      class Func
      >
    const T &push_to_front(Func func) const {
      auto node = queue_.find(func);
      if (node) {
	queue_.remove(node);
	queue_.add_head(node);
      }
      return front();
    }

    void pop() {
      queue_.remove_head();
    }

    bool empty() const {
      return queue_.empty();
    }

  private:

    list<T> queue_;

  };
} // namespace glynos


#endif // __GLYNOS_PUSH_TO_FRONT_QUEUE_INC__
