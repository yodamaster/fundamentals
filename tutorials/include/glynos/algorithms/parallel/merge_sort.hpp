//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_PARALLEL_MERGE_SORT_INC__
# define __GLYNOS_ALGORITHMS_PARALLEL_MERGE_SORT_INC__


# include <glynos/algorithms/merge_sort.hpp>
# include <thread>
# include <future>
# include <vector>

namespace glynos {
  namespace algorithms {
    namespace parallel {
      template <
	class List,
	class Pred
	>
      List merge_sort(const List &list, Pred pred) {
	auto length = list.size();
	if (length != 0) {
	  /**
	   * First work out how many blocks to divide the sequence
	   * into.
	   */
	  typedef decltype(length) length_type;
	  length_type min_per_thread = 25;
	  length_type max_threads = length + (min_per_thread - 1) / min_per_thread;
	  length_type hardware_threads = std::thread::hardware_concurrency();
	  length_type num_threads = std::min(hardware_threads != 0? hardware_threads : 2, max_threads);
	  length_type block_size = length / num_threads;

	  /**
	   * Subdivide the for_each algorithm into `num_threads` tasks.
	   */
	  std::vector<std::thread> threads(num_threads - 1);

	  /**
	   * Find the middle of the sequence.
	   */
	  auto middle = std::begin(list);
	  std::advance(middle, (length >> 1));

	  std::future<List> l1 = std::async(std::launch::async,
					    [](const List &list, Pred pred) {
					      return glynos::algorithms::merge_sort(list, pred);
					    }, List(std::begin(list), middle), pred);

	  List l2 = glynos::algorithms::merge_sort(List(middle, std::end(list)), pred);
	  return details::merge(l1.get(), l2, pred);
	}
	return list;
      }
    } // namespace parallel
  } // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_PARALLEL_MERGE_SORT_INC__
