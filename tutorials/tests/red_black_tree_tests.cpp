//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Red black tree test
#include <boost/test/unit_test.hpp>
#include <glynos/red_black_tree.hpp>
#include <functional>
#include <iostream>
#include <iomanip>


using glynos::red_black_tree;


BOOST_AUTO_TEST_CASE(constructor_test) {
    red_black_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(insert_test) {
    red_black_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK_EQUAL(instance.count(), 1U);
    BOOST_CHECK_EQUAL(instance.height(), 1U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 2);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 2);
}

BOOST_AUTO_TEST_CASE(insert_2_test) {
    red_black_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK_EQUAL(instance.count(), 2U);
    BOOST_CHECK_EQUAL(instance.height(), 2U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 2);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 4);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 8);
}

BOOST_AUTO_TEST_CASE(insert_3_test) {
    red_black_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK(instance.insert(2, 4));
    BOOST_CHECK_EQUAL(instance.count(), 3U);
    BOOST_CHECK_EQUAL(instance.height(), 2U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 2);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 4);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 8);
}

BOOST_AUTO_TEST_CASE(insert_10_test) {
    red_black_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(5, 10));
    BOOST_CHECK(instance.insert(0, 0));
    BOOST_CHECK(instance.insert(6, 12));
    BOOST_CHECK(instance.insert(9, 18));
    BOOST_CHECK(instance.insert(3, 6));
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(2, 4));
    BOOST_CHECK(instance.insert(8, 16));
    BOOST_CHECK(instance.insert(7, 14));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK_EQUAL(instance.count(), 10U);
    BOOST_CHECK_EQUAL(instance.height(), 3U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 0);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 0);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 9);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 18);
}

BOOST_AUTO_TEST_CASE(insert_10_in_order_test) {
    red_black_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(0, 0));
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(2, 4));
    BOOST_CHECK(instance.insert(3, 6));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK(instance.insert(5, 10));
    BOOST_CHECK(instance.insert(6, 12));
    BOOST_CHECK(instance.insert(7, 14));
    BOOST_CHECK(instance.insert(8, 16));
    BOOST_CHECK(instance.insert(9, 18));
    BOOST_CHECK_EQUAL(instance.count(), 10U);
    BOOST_CHECK_EQUAL(instance.height(), 4U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 0);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 0);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 9);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 18);
}

// BOOST_AUTO_TEST_CASE(remove_test) {
//     red_black_tree<int, int, std::less<int> > instance;
//     BOOST_CHECK(instance.insert(1, 2));
//     BOOST_CHECK(instance.insert(4, 8));
//     BOOST_CHECK(instance.insert(2, 4));
//     instance.remove(2);
//     BOOST_CHECK_EQUAL(instance.count(), 2U);
//     BOOST_CHECK_EQUAL(*instance.minimum()->key, 1);
//     BOOST_CHECK_EQUAL(*instance.minimum()->value, 2);
//     BOOST_CHECK_EQUAL(*instance.maximum()->key, 4);
//     BOOST_CHECK_EQUAL(*instance.maximum()->value, 8);
// }
