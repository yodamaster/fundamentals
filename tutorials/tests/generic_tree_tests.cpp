//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE Generic tree test
#include <boost/test/unit_test.hpp>
#include <glynos/generic_tree.hpp>
#include <glynos/list.hpp>
#include "list_io.hpp"
#include <functional>
#include <iostream>


using glynos::generic_tree;
using glynos::list;

#include <boost/spirit/home/phoenix.hpp>
using boost::phoenix::arg_names::arg1;
using boost::phoenix::arg_names::arg2;


BOOST_AUTO_TEST_CASE(constructor_test) {
    generic_tree<int> instance;
    BOOST_CHECK(instance.empty());
}

