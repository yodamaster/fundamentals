//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE List test
#include <boost/test/unit_test.hpp>
#include <glynos/list.hpp>
#include "list_io.hpp"
#include <functional>


using glynos::list;

#include <boost/spirit/home/phoenix.hpp>
using boost::phoenix::arg_names::arg1;
using boost::phoenix::arg_names::arg2;


BOOST_AUTO_TEST_CASE(constructor_test) {
    list<int> instance;
    BOOST_CHECK(instance.empty());
    BOOST_CHECK_EQUAL(instance.count(), 0U);
    BOOST_CHECK(!instance.head_node());
    BOOST_CHECK(!instance.tail_node());
}

BOOST_AUTO_TEST_CASE(add_head_test) {
    list<int> instance;
    instance.add_head(10);
    BOOST_CHECK(!instance.empty());
    BOOST_CHECK_EQUAL(instance.count(), 1U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(add_tail_test) {
    list<int> instance;
    instance.add_tail(10);
    BOOST_CHECK(!instance.empty());
    BOOST_CHECK_EQUAL(instance.count(), 1U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(add_head_2_test) {
    list<int> instance;
    instance.add_head(10);
    instance.add_head(11);
    BOOST_CHECK_EQUAL(instance.count(), 2U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 11);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(add_head_3_test) {
    list<int> instance;
    instance.add_head(10);
    instance.add_head(-2);
    instance.add_head(11);
    BOOST_CHECK_EQUAL(instance.count(), 3U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 11);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(remove_head_test) {
    list<int> instance;
    instance.add_head(10);
    instance.add_head(-2);
    instance.add_head(11);
    instance.remove_head();
    BOOST_CHECK_EQUAL(instance.count(), 2U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, -2);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(remove_head_one_element_test) {
    list<int> instance;
    instance.add_head(10);
    instance.remove_head();
    BOOST_CHECK(instance.empty());
    BOOST_CHECK(!instance.head_node());
    BOOST_CHECK(!instance.tail_node());
}

BOOST_AUTO_TEST_CASE(remove_head_empty_list_test) {
    list<int> instance;
    instance.remove_head();
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(remove_tail_test) {
    list<int> instance;
    instance.add_head(10);
    instance.add_head(-2);
    instance.add_head(11);
    instance.remove_tail();
    BOOST_CHECK_EQUAL(instance.count(), 2U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 11);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, -2);
}

BOOST_AUTO_TEST_CASE(remove_tail_one_element_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.remove_tail();
    BOOST_CHECK(instance.empty());
    BOOST_CHECK(!instance.head_node());
    BOOST_CHECK(!instance.tail_node());
 }

BOOST_AUTO_TEST_CASE(remove_tail_empty_list_test) {
    list<int> instance;
    instance.remove_tail();
    BOOST_CHECK(instance.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor_test) {
    list<int> instance;
    instance.add_head(10);
    instance.add_head(11);

    list<int> copy(instance);

    BOOST_CHECK_EQUAL(instance.count(), 2U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 11);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);

    BOOST_CHECK_EQUAL(copy.count(), 2U);
    BOOST_CHECK_EQUAL(*copy.head_node()->value, 11);
    BOOST_CHECK_EQUAL(*copy.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(swap_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(11);

    list<int> copy;
    copy.swap(instance);

    BOOST_CHECK(instance.empty());

    BOOST_CHECK_EQUAL(copy.count(), 2U);
    BOOST_CHECK_EQUAL(*copy.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*copy.tail_node()->value, 11);
}

BOOST_AUTO_TEST_CASE(assignment_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(11);

    list<int> copy;
    copy = instance;

    BOOST_CHECK_EQUAL(copy.count(), 2U);
    BOOST_CHECK_EQUAL(*copy.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*copy.tail_node()->value, 11);
}

BOOST_AUTO_TEST_CASE(move_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(11);

    list<int> copy = std::move(instance);

    BOOST_CHECK_EQUAL(copy.count(), std::size_t(2));
    BOOST_CHECK_EQUAL(*copy.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*copy.tail_node()->value, 11);
}

BOOST_AUTO_TEST_CASE(move_assignment_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(11);

    list<int> copy;
    copy = std::move(instance);

    BOOST_CHECK_EQUAL(copy.count(), 2U);
    BOOST_CHECK_EQUAL(*copy.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*copy.tail_node()->value, 11);
}

BOOST_AUTO_TEST_CASE(sort_0_elements_test) {
    list<int> instance;
    list<int> sorted = instance.sort(std::less<int>());
    BOOST_CHECK(sorted.empty());
}

BOOST_AUTO_TEST_CASE(sort_1_element_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.sort(std::less<int>());
    BOOST_CHECK_EQUAL(instance.count(), 1U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 10);
}

BOOST_AUTO_TEST_CASE(sort_2_elements_test) {
    list<int> instance;
    instance.add_tail(11);
    instance.add_tail(10);
    instance = instance.sort(std::less<int>());
    BOOST_CHECK_EQUAL(instance.count(), 2U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, 10);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 11);
}

BOOST_AUTO_TEST_CASE(sort_3_elements_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(-2);
    instance.add_tail(11);
    instance = instance.sort(std::less<int>());
    BOOST_CHECK_EQUAL(instance.count(), 3U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, -2);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->value, 10);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 11);
}

BOOST_AUTO_TEST_CASE(sort_4_elements_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(-2);
    instance.add_tail(109);
    instance.add_tail(11);
    instance = instance.sort(std::less<int>());
    BOOST_CHECK_EQUAL(instance.count(), 4U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, -2);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->value, 10);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->value, 11);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 109);
}

BOOST_AUTO_TEST_CASE(sort_5_elements_test) {
    list<int> instance;
    instance.add_tail(10);
    instance.add_tail(-2);
    instance.add_tail(9);
    instance.add_tail(109);
    instance.add_tail(11);
    instance = instance.sort(std::less<int>());
    BOOST_CHECK_EQUAL(instance.count(), 5U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, -2);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->value, 9);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->value, 10);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->next->value, 11);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 109);
}

BOOST_AUTO_TEST_CASE(sort_reverse_elements_test) {
    list<int> instance;
    instance.add_tail(109);
    instance.add_tail(14);
    instance.add_tail(11);
    instance.add_tail(10);
    instance.add_tail(9);
    instance.add_tail(-2);
    instance = instance.sort(std::less<int>());
    BOOST_CHECK_EQUAL(instance.count(), 6U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, -2);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->value, 9);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->value, 10);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->next->value, 11);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->next->next->value, 14);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 109);
}

BOOST_AUTO_TEST_CASE(initializer_list_test) {
    list<int> instance{
        -2, 9, 10, 11, 14, 109 };
    BOOST_CHECK_EQUAL(instance.count(), 6U);
    BOOST_CHECK_EQUAL(*instance.head_node()->value, -2);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->value, 9);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->value, 10);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->next->value, 11);
    BOOST_CHECK_EQUAL(*instance.head_node()->next->next->next->next->value, 14);
    BOOST_CHECK_EQUAL(*instance.tail_node()->value, 109);
}

BOOST_AUTO_TEST_CASE(equality_test_1) {
    list<int> instance1{
        -2, 9, 10, 11, 14, 109 };
    list<int> instance2{
        -2, 9, 10, 11, 14, 109 };
    BOOST_CHECK(instance1 == instance2);
}

BOOST_AUTO_TEST_CASE(equality_test_2) {
    list<int> instance1{ -2 };
    list<int> instance2{ -2 };
    BOOST_CHECK(instance1 == instance2);
}

BOOST_AUTO_TEST_CASE(equality_test_3) {
    list<int> instance1;
    list<int> instance2;
    BOOST_CHECK(instance1 == instance2);
}

BOOST_AUTO_TEST_CASE(inequality_test) {
    list<int> instance1{
        -2, 9, 10, 11, 14, 109 };
    list<int> instance2{
        -2, 9, 10, 11, 14 };
    BOOST_CHECK(instance1 != instance2);
}
