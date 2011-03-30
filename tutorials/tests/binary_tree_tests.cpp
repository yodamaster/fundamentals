//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Binary tree test
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <glynos/binary_tree.hpp>
#include <glynos/list.hpp>
#include <functional>
#include <iostream>


using glynos::binary_tree;
using glynos::list;

#include <boost/spirit/home/phoenix.hpp>
using boost::phoenix::arg_names::arg1;
using boost::phoenix::arg_names::arg2;

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


BOOST_AUTO_TEST_CASE(constructor_test) {
    binary_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(insert_test) {
    binary_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK_EQUAL(instance.count(), 1U);
    BOOST_CHECK_EQUAL(instance.height(), 1U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 2);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 2);
}

BOOST_AUTO_TEST_CASE(insert_2_test) {
    binary_tree<int, int, std::less<int> > instance;
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
    binary_tree<int, int, std::less<int> > instance;
    BOOST_CHECK(instance.insert(1, 2));
    BOOST_CHECK(instance.insert(4, 8));
    BOOST_CHECK(instance.insert(2, 4));
    BOOST_CHECK_EQUAL(instance.count(), 3U);
    BOOST_CHECK_EQUAL(instance.height(), 3U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 1);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 2);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 4);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 8);
}

BOOST_AUTO_TEST_CASE(insert_10_test) {
    binary_tree<int, int, std::less<int> > instance;
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
    BOOST_CHECK_EQUAL(instance.height(), 5U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 0);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 0);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 9);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 18);
}

BOOST_AUTO_TEST_CASE(insert_10_in_order_test) {
    binary_tree<int, int, std::less<int> > instance;
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
    BOOST_CHECK_EQUAL(instance.height(), 10U);
    BOOST_CHECK_EQUAL(*instance.minimum()->key, 0);
    BOOST_CHECK_EQUAL(*instance.minimum()->value, 0);
    BOOST_CHECK_EQUAL(*instance.maximum()->key, 9);
    BOOST_CHECK_EQUAL(*instance.maximum()->value, 18);
}

struct copy_key_to_list {
    list<int> &keys;
    copy_key_to_list(list<int> &keys) : keys(keys) {}
    void operator () (int key, int) const {
        keys.add_tail(key);
    }
};

BOOST_AUTO_TEST_CASE(preorder_walk_test) {
    binary_tree<int, int, std::less<int> > instance;
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
    instance.preorder_walk(copy_key_to_list(l2));
    BOOST_CHECK(l1 == l2);
}

BOOST_AUTO_TEST_CASE(inorder_walk_test) {
    binary_tree<int, int, std::less<int> > instance;
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

    list<int> l1, l2;
    l1.add_tail(0);
    l1.add_tail(1);
    l1.add_tail(2);
    l1.add_tail(3);
    l1.add_tail(4);
    l1.add_tail(5);
    l1.add_tail(6);
    l1.add_tail(7);
    l1.add_tail(8);
    l1.add_tail(9);
    instance.inorder_walk(copy_key_to_list(l2));
    BOOST_CHECK(l1 == l2);
}

BOOST_AUTO_TEST_CASE(postorder_walk_test) {
    binary_tree<int, int, std::less<int> > instance;
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

    list<int> l1, l2;
    l1.add_tail(4);
    l1.add_tail(3);
    l1.add_tail(2);
    l1.add_tail(1);
    l1.add_tail(0);
    l1.add_tail(7);
    l1.add_tail(8);
    l1.add_tail(9);
    l1.add_tail(6);
    l1.add_tail(5);
    instance.postorder_walk(copy_key_to_list(l2));
    BOOST_CHECK(l1 == l2);
}

BOOST_AUTO_TEST_CASE(levelorder_walk_test) {
    binary_tree<int, int, std::less<int> > instance;
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

    list<int> l1, l2;
    l1.add_tail(5);
    l1.add_tail(0);
    l1.add_tail(6);
    l1.add_tail(1);
    l1.add_tail(9);
    l1.add_tail(2);
    l1.add_tail(8);
    l1.add_tail(3);
    l1.add_tail(7);
    l1.add_tail(4);
    instance.levelorder_walk(copy_key_to_list(l2));
    BOOST_CHECK(l1 == l2);
}

BOOST_AUTO_TEST_CASE(remove_test) {
    binary_tree<int, int, std::less<int> > instance;
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
