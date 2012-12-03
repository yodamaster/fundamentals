//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <thread>
#include <mutex>
#include <iostream>
#include "bounded_buffer.hpp"


glynos::bounded_buffer<int> buffer(5);
std::mutex io_monitor;

void send() {
  for (int i = 0; i < 50; ++i) {
    {
      std::lock_guard<std::mutex> lock(io_monitor);
      std::cout << "Sending: " << i << std::endl;
    }
    buffer.consume(i);
  }
}

void receive() {
  for (int i = 0; i < 100; ++i) {
    int n = buffer.produce();
    {
      std::lock_guard<std::mutex> lock(io_monitor);
      std::cout << "Receiving: " << n << std::endl;
    }
  }
}

int
main(int argc, char *argv[]) {

  std::thread t1(send);
  std::thread t2(send);
  std::thread t3(receive);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
