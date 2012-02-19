//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm>
#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <boost/timer.hpp>
#include <boost/thread/thread.hpp>
#include <glynos/algorithms/parallel/for_each.hpp>

using namespace glynos::algorithms;

int
main(int argc, char *argv[]) {

	boost::timer t;

    /**
     * Time the standard for_each algorithm.
     */
    t.restart();
    {
        std::vector<std::string> vec_str{
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
        	"Aston Vanilla",
        	"Queens Park Rangers",
        	"Blackburn Rovers",
        	"Wolverhampton Wanderers",
        	"Bolton Wanderers",
        	"Wigan",
        };

        std::for_each(vec_str.begin(), vec_str.end(),
					  [] (std::string &team) { team += " FC"; });

		std::for_each(vec_str.begin(), vec_str.end(),
					  [] (const std::string &team) { std::cout << team << std::endl; });
	}
    std::cout << "std::for_each: " << t.elapsed() << std::endl;

    /**
     * Time the parallel for_each algorithm.
     */
    t.restart();
    {
        std::vector<std::string> vec_str{
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
        	"Aston Vanilla",
        	"Queens Park Rangers",
        	"Blackburn Rovers",
        	"Wolverhampton Wanderers",
        	"Bolton Wanderers",
        	"Wigan",
        };

        parallel::for_each(vec_str.begin(), vec_str.end(),
						   [] (std::string &team) { team += " FC"; });

		std::for_each(vec_str.begin(), vec_str.end(),
					  [] (const std::string &team) { std::cout << team << std::endl; });
    }
    std::cout << "parallel::for_each: " << t.elapsed() << std::endl;

    return 0;
}
