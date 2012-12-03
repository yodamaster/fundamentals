//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__
# define __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__

# include <future>
# include <algorithm>
# include <vector>

namespace glynos {
  namespace algorithms {
    namespace parallel {
      template <
	class I,
	class F
	>
      F for_each(I first, I last, F f) {
	auto length = std::distance(first, last);
	typedef decltype(length) dist_type;
	if (length != 0) {
	  /**
	   * First work out how many blocks to divide the sequence
	   * into.
	   */
	  dist_type min_per_thread = 25;
	  dist_type max_threads = length + (min_per_thread - 1) / min_per_thread;
	  dist_type hardware_threads = std::thread::hardware_concurrency();
	  dist_type num_threads = std::min(hardware_threads != 0? hardware_threads : 2, max_threads);
	  dist_type block_size = length / num_threads;

	  /**
	   * Subdivide the for_each algorithm into `num_threads` tasks.
	   */
	  std::vector<std::future<F> > results(num_threads - 1);

	  auto block_begin = first;
	  for (auto &result : results) {
            auto block_end = block_begin;
            std::advance(block_end, block_size);
            result = std::async(std::for_each<I, F>, block_begin, block_end, f);
            block_begin = block_end;
	  }

	  /**
	   * Finally, run the last task in the current thread.
	   */
	  std::for_each(block_begin, last, f);

	  /**
	   * Don't exit until tasks are complete.
	   */
	  for (auto &result : results) {
            result.get();
	  }
	}
	return f;
      }
    } // namespace parallel
  } // namespace algorithms
} // namespace glynos

#endif // __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__
