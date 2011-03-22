//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// This is a very simple implementation of merge sort.


#include <glynos/algorithms/merge_sort.hpp>
#include <list>
#include <string>
#include <functional>
#include <boost/spirit/home/phoenix.hpp>
#include <iostream>


int
main(int argc, char *argv[]) {
    using boost::phoenix::arg_names::arg1;

    std::list<std::string> instance;
    instance.push_back("Manchester United");
    instance.push_back("Liverpool");
    instance.push_back("Chelsea");
    instance.push_back("Aston Villa");
    instance.push_back("Arsenal");
    instance.push_back("Everton");
    instance.push_back("Wigan");
    instance.push_back("West Ham United");
    instance.push_back("Manchester City");
    instance.push_back("Sunderland");
    instance.push_back("Fulham");
    instance.push_back("Bolton Wanderers");
    instance.push_back("Hull");
    instance.push_back("Portsmouth");
    instance.push_back("Newcastle United");
    instance.push_back("Tottenham Hotspurs");
    instance.push_back("Stoke City");
    instance.push_back("Blackburn Rovers");
    instance.push_back("Middlesbrough");
    instance.push_back("West Bromwich Albion");

    std::for_each(instance.begin(), instance.end(), std::cout << arg1 << ", ");
    std::cout << std::endl;
    std::list<std::string> sorted =
        glynos::algorithms::merge_sort(instance, std::less<std::string>());
    std::for_each(sorted.begin(), sorted.end(), std::cout << arg1 << ", ");
    std::cout << std::endl;

    return 0;
}
