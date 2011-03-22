//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Concurrent queue tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <glynos/concurrent/queue.hpp>


using glynos::concurrent::queue;


BOOST_AUTO_TEST_CASE(constructor_test) {
    queue<int> instance;
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(push_test) {
    queue<int> instance;

    instance.push(10);
    // std::unique_ptr<int>
}
