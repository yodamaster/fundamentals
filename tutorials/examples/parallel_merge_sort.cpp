//             Copyright Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <glynos/algorithms/parallel/merge_sort.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <limits>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>


int
main(int argc, char *argv[]) {
	using std::chrono::system_clock;
	using glynos::algorithms::parallel::merge_sort;

    std::vector<int> vec_int(1000000);
	boost::generate(vec_int, &std::rand);

	system_clock::time_point before = system_clock::now();
    vec_int = merge_sort(vec_int, std::less<int>());
	std::cout << "merge_sort took "
			  << ((system_clock::now() - before).count() / 1000) << " ms" << std::endl;

	return 0;
}
