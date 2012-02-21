//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_PARALLEL_MERGE_SORT_INC__
# define __GLYNOS_ALGORITHMS_PARALLEL_MERGE_SORT_INC__


# include <boost/thread/thread.hpp>
# include <boost/thread/condition_variable.hpp>
# include <boost/thread/future.hpp>
# include <boost/iterator/iterator_traits.hpp>
# include <boost/shared_ptr.hpp>
# include <glynos/algorithms/merge_sort.hpp>


namespace glynos {
namespace algorithms {
namespace parallel {
template <
    class List,
    class Pred
    >
List merge_sort(const List &list, const Pred &pred) {
	return glynos::algorithms::merge_sort(list, pred);
}
} // namespace parallel
} // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_PARALLEL_MERGE_SORT_INC__
