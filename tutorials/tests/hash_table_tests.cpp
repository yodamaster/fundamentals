//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Hash table tests
#include <boost/test/unit_test.hpp>
#include <glynos/hash_table.hpp>
#include <iostream>
#include <cassert>

using glynos::hash_table;
using glynos::list;

template <
    class T
    >
std::ostream &operator << (std::ostream &os, const glynos::list<T> &list) {
    std::shared_ptr<const typename glynos::list<T>::node_type> node;
    for (node = list.head(); node; node = node->next) {
        os << *node->value << ", ";
    }
    return os;
}


unsigned int my_hash(int x) {
    return x % 701;
}

typedef unsigned int (*Hash)(int);

BOOST_AUTO_TEST_CASE(constructor_test) {
    hash_table<int, int, Hash> instance;
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(insert_test) {
    hash_table<int, int, Hash> instance(100000, &my_hash);
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK_EQUAL(instance.count(), 1U);
}

BOOST_AUTO_TEST_CASE(insert_2_test) {
    hash_table<int, int, Hash> instance(100000, &my_hash);
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK_EQUAL(instance.count(), 2U);
}

BOOST_AUTO_TEST_CASE(insert_3_test) {
    hash_table<int, int, Hash> instance(100000, &my_hash);
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK(instance.insert(2, 4));
    BOOST_CHECK_EQUAL(instance.count(), 3U);
}

BOOST_AUTO_TEST_CASE(walk_test) {
    hash_table<int, int, Hash> instance(100000, &my_hash);
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

    list<int> l1, l2;
    l1.add_tail(5);
    l1.add_tail(0);
    l1.add_tail(3);
    l1.add_tail(1);
    l1.add_tail(2);
    l1.add_tail(4);
    l1.add_tail(6);
    l1.add_tail(9);
    l1.add_tail(8);
    l1.add_tail(7);
}

BOOST_AUTO_TEST_CASE(remove_test) {
    hash_table<int, int, Hash> instance(100000, &my_hash);
    BOOST_CHECK(instance.insert(5, 10));
    BOOST_CHECK(instance.insert(0, 0));
    BOOST_CHECK(instance.insert(6, 12));
    BOOST_CHECK(instance.insert(9, 18));
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(2, 4));
    BOOST_CHECK(instance.insert(8, 16));
    BOOST_CHECK(instance.insert(3, 6));
    BOOST_CHECK(instance.insert(7, 14));
    BOOST_CHECK(instance.insert(4, 8));
    instance.remove(8);
    BOOST_CHECK_EQUAL(instance.count(), 9U);
    BOOST_CHECK(!instance.find(8));
}
