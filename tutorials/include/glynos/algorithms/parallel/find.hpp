//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_PARALLEL_FIND_INC__
# define __GLYNOS_ALGORITHMS_PARALLEL_FIND_INC__

# include <algorithm>
# include <thread>
# include <future>
# include <vector>


namespace glynos {
namespace algorithms {
namespace parallel {
template <
    class I,
    class V
    >
I find(I first, I last, const V &v) {
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

        std::function<void (I, I, const V &, std::promise<I> *, std::atomic<bool> *)>
            find_helper =
            []  (I first, I last, const V &v, std::promise<I> *result, std::atomic<bool> *done) {
            try {
                for (auto it = first; (it != last) && !done->load(); ++it) {
                    if (v == *it) {
                        result->set_value(it);
                        done->store(true);
                        break;
                    }
                }
            }
            catch (...) {
                try {
                    result->set_exception(std::current_exception());
                    done->store(true);
                }
                catch (...) {
                }
            }
        };

        /**
         * Subdivide the find algorithm into `num_threads` tasks.
         */
        std::promise<I> result;
        std::atomic<bool> done(false);
		std::vector<std::thread> threads(num_threads - 1);

        auto block_begin = first;
        for (auto &thread : threads) {
            auto block_end = block_begin;
            std::advance(block_end, block_size);
            thread = std::move(std::thread(find_helper, block_begin, block_end, v, &result, &done));
            block_begin = block_end;
        }

        find_helper(block_begin, last, v, &result, &done);

        /**
         * Don't exit until tasks are complete.
         */
        for (auto &thread : threads) {
            thread.join();
        }

        if (done.load()) {
            return result.get_future().get();
        }
    }

    return last;
}
} // namespace parallel
} // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_PARALLEL_FIND_INC__
