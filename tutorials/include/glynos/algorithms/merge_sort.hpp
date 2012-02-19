//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_MERGE_SORT_INC__
# define __GLYNOS_ALGORITHMS_MERGE_SORT_INC__


# include <algorithm>


namespace glynos {
namespace algorithms {
namespace details {
template <
    class List,
    class Pred
    >
List merge(const List &left, const List &right, Pred pred) {
    List result;
    auto left_it = std::begin(left), right_it = std::begin(right);
    while ((left_it != left.end()) ||
           (right_it != right.end())) {
        if ((left_it != left.end()) &&
            (right_it != right.end())) {
            if (pred(*left_it, *right_it)) {
                result.push_back(*left_it++);
            }
            else {
                result.push_back(*right_it++);
            }
        }
        else if (left_it != left.end()) {
            result.push_back(*left_it++);
        }
        else {
            result.push_back(*right_it++);
        }
    }
    return result;
}
}// namespace details

template <
    class List,
    class Pred
    >
List merge_sort(const List &list, const Pred &pred) {
    typedef typename List::size_type size_type;
    typedef typename List::const_iterator iterator;

    size_type size = list.size();

    /**
     * If there is only one element, it's already sorted.  This is the
     * termination condition.
     */
    if (size <= 1) {
        return list;
    }

    /**
     * Find the middle of the sequence.
     */
    iterator middle = std::begin(list);
    std::advance(middle, (size >> 1));

    /**
     * Recursively call merge sort on the first and the second part of
     * the sequence.
     */
    return details::merge(merge_sort(List(std::begin(list), middle), pred),
                          merge_sort(List(middle, std::end(list)), pred),
                          pred);
}
} // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_MERGE_SORT_INC__
