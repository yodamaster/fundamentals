//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <glynos/algorithms/parallel/count.hpp>
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

  std::vector<int> vec_int(100000000);
  std::generate(std::begin(vec_int), std::end(vec_int), &std::rand);

  /**
   * Time the standard count algorithm.
   */
  {
    system_clock::time_point before = system_clock::now();
    int count = std::count(vec_int.begin(), vec_int.end(), 42);
    system_clock::time_point after = system_clock::now();
    std::cout << "Finished std::count " << count << " : " << duration_cast<milliseconds>(after - before).count() << std::endl;
  }

  /**
   * Time the parallel count algorithm.
   */
  {
    system_clock::time_point before = system_clock::now();
    int count = parallel::count(vec_int.begin(), vec_int.end(), 42);
    system_clock::time_point after = system_clock::now();
    std::cout << "Finished parallel::count " << count << " : " << duration_cast<milliseconds>(after - before).count() << std::endl;
  }

  return 0;
}
