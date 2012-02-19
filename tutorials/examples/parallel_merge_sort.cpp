//             Copyright Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptors.hpp>
#include <vector>
#include <string>
#include <list>
#include <functional>
#include <thread>
#include <iostream>


int
main(int argc, char *argv[]) {
	std::vector<double> vec_dbl(100000000);
	boost::generate(vec_dbl, &std::rand);
	boost::for_each(vec_dbl, [](double &arg){arg /= INT_MAX;});


	std::cout << vec_dbl.front() << std::endl;
	std::cout << vec_dbl.back() << std::endl;

	return 0;
}
