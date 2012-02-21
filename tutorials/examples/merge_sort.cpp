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

	auto less = [](double v1, double v2) { return v1 < v2; };

	std::vector<double> vec_dbl(1000000);
	boost::generate(vec_dbl, &std::rand);
	boost::for_each(vec_dbl, [](double &arg){arg /= std::numeric_limits<int>::max();});

	std::chrono::system_clock::time_point before = std::chrono::system_clock::now();
    vec_dbl = merge_sort(vec_dbl, less);
	std::cout << "merge_sort took "
			  << ((std::chrono::system_clock::now() - before).count() / 1000) << " ms" << std::endl;

    return 0;
}
