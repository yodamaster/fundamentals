//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_MERGE_SORT_INC__
# define __GLYNOS_ALGORITHMS_MERGE_SORT_INC__


# include <algorithm>
# include <vector>


namespace glynos {
namespace algorithms {
namespace details {
template <
    class List,
    class Pred
    >
List merge(const List &left, const List &right, Pred pred) {
    List result;
	std::merge(std::begin(left), std::end(left),
			   std::begin(right), std::end(right),
			   std::back_inserter(result), pred);
    return result;
}
}// namespace details

template <
    class List,
    class Pred
    >
List merge_sort(const List &list, const Pred &pred) {

    /**
     * If there is only one element, it's already sorted.  This is the
     * termination condition.
     */
    auto size = list.size();
    if (size <= 1) {
        return list;
    }

    /**
     * Find the middle of the sequence.
     */
    auto middle = std::begin(list);
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
