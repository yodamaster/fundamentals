//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <glynos/algorithms/merge_sort.hpp>
#include <vector>
#include <string>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <iostream>


int
main(int argc, char *argv[]) {
	using glynos::algorithms::merge_sort;

    std::vector<std::string> teams{
        "Manchester City",
        "Manchester United",
        "Tottenham Hotspurs",
        "Arsenal",
        "Chelsea",
        "Newcastle United",
        "Liverpool",
        "Norwich City",
        "Sunderland",
        "Everton",
        "Swansea City",
        "Fulham",
        "Stoke City",
        "West Bromwich Albion",
        "Aston Villa",
        "Queens Park Rangers",
        "Blackburn Rovers",
        "Wolverhampton Wanderers",
        "Bolton Wanderers",
        "Wigan",
    };

    boost::for_each(teams, [](const std::string &team) { std::cout << team << ", "; });
    std::cout << std::endl;
	teams = merge_sort(teams, std::less<std::string>());
    boost::for_each(teams, [](const std::string &team) { std::cout << team << ", "; });
    std::cout << std::endl;

    return 0;
}
