#ifndef __GLYNOS_ALGORITHMS_PARALLEL_SUM_INC__
# define __GLYNOS_ALGORITHMS_PARALLEL_SUM_INC__

# include <future>
# include <algorithm>


namespace glynos {
namespace algorithms {
namespace parallel {
template<typename I>
int sum(I first, I last)
{
    typename I::difference_type length = last - first;
    if(length < 1000)
	{
        return std::accumulate(first, last, 0);
	}

    I mid = first + (length / 2);
    auto sum_second = std::async(std::launch::async, sum<I>, mid, last);
    int sum_first = sum(first, mid);
    return sum_first + sum_second.get();
}
} // namespace parallel
} // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_PARALLEL_SUM_INC__
