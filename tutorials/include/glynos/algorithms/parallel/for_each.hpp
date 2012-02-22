//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__
# define __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__

# include <thread>
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
    if (length != 0) {
        /**
         * First work out how many blocks to divide the sequence
         * into.
         */
        decltype(length) min_per_thread = 25;
        decltype(length) max_threads = length + (min_per_thread - 1) / min_per_thread;
        decltype(length) hardware_threads = std::thread::hardware_concurrency();
        decltype(length) num_threads = std::min(hardware_threads != 0? hardware_threads : 2, max_threads);
        decltype(length) block_size = length / num_threads;

        /**
         * Subdivide the for_each algorithm into `num_threads` tasks.
         */
        std::vector<std::thread> threads(num_threads - 1);

        auto block_begin = first;
        for (auto &thread : threads) {
            auto block_end = block_begin;
            std::advance(block_end, block_size);
            thread = std::move(std::thread(std::for_each<I, F>, block_begin, block_end, f));
            block_begin = block_end;
        }

        /**
         * Finally, run the last task in the current thread.
         */
        std::for_each(block_begin, last, f);

        /**
         * Don't exit until tasks are complete.
         */
        for (auto &thread : threads) {
            thread.join();
        }
    }
    return f;
}
} // namespace parallel
} // namespace algorithms
} // namespace glynos

#endif // __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__
