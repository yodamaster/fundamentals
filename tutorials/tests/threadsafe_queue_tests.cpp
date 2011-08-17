//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Thread-safe queue tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <glynos/threadsafe/queue.hpp>


using glynos::threadsafe::queue;
using glynos::threadsafe::empty_queue;


BOOST_AUTO_TEST_CASE(test_constructor) {
    queue<int> instance;
    BOOST_CHECK_EQUAL(instance.count(), 0UL);
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(test_push_pop) {
    queue<int> instance;
    instance.push(10);
    BOOST_CHECK_EQUAL(instance.count(), 1UL);
    std::shared_ptr<int> result = instance.pop();
    BOOST_CHECK_EQUAL(*result, 10);
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(test_push_2_pop) {
    queue<int> instance;
    instance.push(10);
    instance.push(20);
    BOOST_CHECK_EQUAL(instance.count(), 2UL);
    std::shared_ptr<int> result = instance.pop();
    BOOST_CHECK_EQUAL(*result, 10);
    BOOST_CHECK_EQUAL(instance.count(), 1UL);
    result = instance.pop();
    BOOST_CHECK_EQUAL(*result, 20);
}

BOOST_AUTO_TEST_CASE(test_pop_empty_queue) {
    queue<int> instance;
    BOOST_CHECK_THROW(instance.pop(), empty_queue);
}
