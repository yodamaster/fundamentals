//            Copyright (c) Glyn Matthews 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// This is a very simple implementation of merge sort.


#include <glynos/algorithms/merge_sort.hpp>
#include <vector>
#include <functional>
#include <iostream>
#include <chrono>
#include <limits>
#include <cmath>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>


int
main(int argc, char *argv[]) {
	using glynos::algorithms::merge_sort;

    std::vector<int> vec_int(1000000);
	boost::generate(vec_int, &std::rand);

	std::chrono::system_clock::time_point before = std::chrono::system_clock::now();
    vec_int = merge_sort(vec_int, std::less<int>());
	std::cout << "merge_sort took "
			  << ((std::chrono::system_clock::now() - before).count() / 1000) << " ms" << std::endl;

    return 0;
}
