#ifndef __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__
# define __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__


# include <thread>
# include <memory>
# include <algorithm>
# include <iterator>
# include <vector>


namespace glynos {
namespace algorithms {
namespace concurrent {
namespace details {
/**
 * This is an adapter around std::for_each to make it easier to create
 * a std::packaged_task.
 */
template <
    class I,
    class F
    >
struct for_each_helper {
    I first, last;
    F f;

    for_each_helper(I first, I last, F f)
        : first(first), last(last), f(f) {

    }

    void operator () () {
        std::for_each(first, last, f);
    }
};



template <
    class I,
    class F
    >
inline
for_each_helper<I, F> make_helper(I first, I last, F f) {
    return for_each_helper<I, F>(first, last, f);
}
} // namespace details


template <
    class I,
    class F
    >
F parallel_for_each(I first, I last, F f) {
    typedef typename std::iterator_traits<T>::difference_type difference_type;

    const difference_type length = std::distance(first, last);
    if (length != 0) {
        /**
         * First work out how many blocks to divide the sequence
         * into.
         */
        const difference_type min_per_thread = 25;
        const difference_type max_threads = length + (min_per_thread - 1) / min_per_thread;
        const difference_type hardware_threads = std::thread::hardware_concurrency();
        const difference_type num_threads = std::min(hardware_threads != 0? hardware_threads : 2,
                                                     max_threads);
        const difference_type block_size = length / num_threads;

        /**
         * Subdivide the for_each algorithm into `num_threads` tasks.
         */
        std::vector<std::shared_ptr<std::unique_future<void> > > futures(num_threads - 1);
        std::vector<std::shared_ptr<std::thread> > threads(num_threads - 1);

        I block_start = first;
        for (difference_type i = 0; i < num_threads - 1; ++i) {
            I block_end = block_start;
            std::advance(block_end, block_size);
            /**
             * For each thread, start a task.
             */
            std::packaged_task<void> task(
                details::make_helper(block_start, block_end, f));
            // futures[i].reset(new std::unique_future<void>(std::move(task.get_future())));
            futures[i].reset(new std::unique_future<void>(task.get_future()));
            threads[i].reset(new std::thread(std::move(task)));
            block_start = block_end;
        }

        /**
         * Finally, run the last task in the current thread.
         */
        std::for_each(block_start, last, f);

        /**
         * Don't exit until tasks are complete.
         */
        for (difference_type i = 0; i < num_threads - 1; ++i) {
            futures[i]->get();
        }
    }
    return f;
}
} // namespace concurrent
} // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_CONCURRENT_PARALLEL_FOR_EACH_INC__
