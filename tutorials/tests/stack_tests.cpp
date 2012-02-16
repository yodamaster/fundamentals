//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Stack tests
#include <boost/test/unit_test.hpp>
#include <glynos/stack.hpp>


using glynos::stack;


BOOST_AUTO_TEST_CASE(test_constructor) {
    stack<int> instance;
    BOOST_CHECK_EQUAL(instance.count(), 0UL);
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(test_push_pop) {
    stack<int> instance;
    instance.push(10);
    BOOST_CHECK(!instance.empty());
    BOOST_CHECK_EQUAL(instance.count(), 1UL);
    BOOST_CHECK_EQUAL(instance.top(), 10);
    instance.pop();
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(test_push_2_pop) {
    stack<int> instance;
    instance.push(10);
    instance.push(20);
    BOOST_CHECK_EQUAL(instance.count(), 2UL);
    BOOST_CHECK_EQUAL(instance.top(), 20);
    instance.pop();
    BOOST_CHECK_EQUAL(instance.count(), 1UL);
    BOOST_CHECK_EQUAL(instance.top(), 10);
}

BOOST_AUTO_TEST_CASE(test_pop_empty_stack) {
    stack<int> instance;
    instance.pop();
    BOOST_CHECK(instance.empty());
}
