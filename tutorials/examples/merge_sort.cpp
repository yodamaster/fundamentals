//            Copyright (c) Glyn Matthews 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// This is a very simple implementation of merge sort.


#include <iterator>
#include <vector>
#include <stack>
#include <string>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <iostream>


namespace {
  template <class Container, class Pred>
  Container merge(const Container &left, const Container &right, Pred pred) {
    Container result;
    auto left_it = std::begin(left), left_end = std::end(left),
      right_it = std::begin(right), right_end = std::end(right);

    while ((left_it != left_end) || (right_it != right_end)) {
      if ((left_it != left_end) && (right_it != right_end)) {
	if (pred(*left_it, *right_it)) {
	  result.push_back(*left_it);
	  ++left_it;
	}
	else {
	  result.push_back(*right_it);
	  ++right_it;
	}
      }
      else if (left_it != left_end) {
	result.push_back(*left_it);
	++left_it;
      }
      else if (right_it != right_end) {
	result.push_back(*right_it);
	++right_it;
      }
    }
    return result;
  }

  template <class Container, class Pred>
  Container merge_sortr(const Container &unsorted, Pred pred) {
    if (unsorted.size() <= 1) {
      return unsorted;
    }

    auto midpoint_it = std::begin(unsorted);
    std::advance(midpoint_it, unsorted.size() / 2);
    auto left = merge_sortr(Container(std::begin(unsorted), midpoint_it), pred);
    auto right = merge_sortr(Container(midpoint_it, std::end(unsorted)), pred);
    return merge(left, right, pred);
  }

  template <class Container, class Pred>
  Container merge_sorti(const Container &unsorted, Pred pred) {
    if (unsorted.size() == 0) {
      return unsorted;
    }

    std::stack<Container> lsts;
    Container result;

    while (!lsts.empty()) {
      Container tmp = lsts.top();
      lsts.pop();


    }
    return result;
  }
} // namespace


int
main(int argc, char *argv[]) {
  std::vector<std::string> teams;
  teams.push_back("Manchester City");
  teams.push_back("Manchester United");
  teams.push_back("Tottenham Hotspurs");
  teams.push_back("Arsenal");
  teams.push_back("Chelsea");
  teams.push_back("Newcastle United");
  teams.push_back("Liverpool");
  teams.push_back("Norwich City");
  teams.push_back("Sunderland");
  teams.push_back("Everton");
  teams.push_back("Swansea City");
  teams.push_back("Fulham");
  teams.push_back("Stoke City");
  teams.push_back("West Bromwich Albion");
  teams.push_back("Aston Villa");
  teams.push_back("Queens Park Rangers");
  teams.push_back("Blackburn Rovers");
  teams.push_back("Wolverhampton Wanderers");
  teams.push_back("Bolton Wanderers");
  teams.push_back("Wigan");

  boost::for_each(teams, [](const std::string &team) { std::cout << team << ", "; });
  std::cout << std::endl;
  {
    auto sorted_teams = merge_sortr(teams, std::less<std::string>());
    boost::for_each(sorted_teams, [](const std::string &team) { std::cout << team << ", "; });
    std::cout << std::endl;
  }

  {
    auto sorted_teams = merge_sorti(teams, std::less<std::string>());
    boost::for_each(sorted_teams, [](const std::string &team) { std::cout << team << ", "; });
    std::cout << std::endl;
  }

  return 0;
}
