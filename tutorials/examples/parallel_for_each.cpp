//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <glynos/algorithms/parallel/for_each.hpp>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace glynos::algorithms;

int
main(int argc, char *argv[]) {

  std::cout << "There are " << std::thread::hardware_concurrency() << " hardware threads." << std::endl;

  std::vector<double> vec_dbl(100, 0.);

  /**
   * Time the standard for_each algorithm.
   */
  {
    system_clock::time_point before = system_clock::now();
    std::for_each(vec_dbl.begin(), vec_dbl.end(),
		  [] (double value) { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
    system_clock::time_point after = system_clock::now();
    std::cout << "Finished std::for_each " << duration_cast<milliseconds>(after - before).count() << std::endl;
  }

  /**
   * Time the parallel for_each algorithm.
   */
  {
    system_clock::time_point before = system_clock::now();
    parallel::for_each(vec_dbl.begin(), vec_dbl.end(),
		       [] (double value) { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
    system_clock::time_point after = system_clock::now();
    std::cout << "Finished parallel::for_each " << duration_cast<milliseconds>(after - before).count() << std::endl;
  }

  return 0;
}
