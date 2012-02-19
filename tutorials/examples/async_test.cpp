//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <iostream>
#include <glynos/algorithms/parallel/sum.hpp>

using namespace glynos::algorithms;

int main(int argc, char *argv[]) {
    //std::vector<int> v(10000, 1);
    //std::cout << "The sum is " << parallel::sum(v.begin(), v.end()) << std::endl;

	std::future<int> result = std::async(std::launch::async, []() { return 10; });
	std::cout << result.get() << std::endl;

	return 0;
}
