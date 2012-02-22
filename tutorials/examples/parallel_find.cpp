//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <glynos/algorithms/parallel/find.hpp>
#include <vector>
#include <chrono>
#include <iostream>

using std::chrono::system_clock;
using namespace glynos::algorithms;

int
main(int argc, char *argv[]) {

    std::vector<int> vec_int(100000000);
    //std::vector<int> vec_int(100);
    std::generate(std::begin(vec_int), std::end(vec_int), &std::rand);
    vec_int[5734209] = 42;
    //vec_int[57] = 42;

    /**
     * Time the standard find algorithm.
     */
    {
        system_clock::time_point before = system_clock::now();
        auto it = std::find(vec_int.begin(), vec_int.end(), 42);
        system_clock::time_point after = system_clock::now();
        std::cout << "Finished std::find " << std::boolalpha << !(it == vec_int.end()) << " : " << ((after - before).count() / 1000000.) << std::endl;
    }

    /**
     * Time the parallel find algorithm.
     */
    {
        system_clock::time_point before = system_clock::now();
        auto it = parallel::find(vec_int.begin(), vec_int.end(), 42);
        system_clock::time_point after = system_clock::now();
        std::cout << "Finished parallel::find " << std::boolalpha << !(it == vec_int.end()) << " : " << ((after - before).count() / 1000000.) << std::endl;
    }

    return 0;
}
