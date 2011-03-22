//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_HEAP_SORT_INC__
# define __GLYNOS_ALGORITHMS_HEAP_SORT_INC__


# include <algorithm>


namespace glynos {
namespace algorithms {
namespace details {
template <
    class Iter,
    class Pred
    >
void sift_down(Iter first, Iter last, Pred pred) {

}

template <
    class Iter,
    class Pred
    >
void make_heap(Iter begin, Iter end, Pred pred) {

}
} // namespace details

template <
    class Iter,
    class Pred
    >
void heap_sort(Iter begin, Iter end, Pred pred) {
    // heapify(begin, end, pred);
    std::make_heap(begin, end);
    std::sort_heap(begin, end);

}
} // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_HEAP_SORT_INC__
