//            Copyright (c) Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <iterator>
#include <vector>
#include <stack>
#include <string>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <iostream>


namespace {
  template <class Container, class Pred>
  Container quick_sortr(const Container &unsorted, Pred pred) {
    Container sorted;
    if (!unsorted.empty()) {
      auto pivot = unsorted[0];

      Container left, right;
      auto it = std::begin(unsorted), last = std::end(unsorted);
      ++it;
      while (it != last) {
	if (pred(*it, pivot)) {
	  left.push_back(*it);
	}
	else {
	  right.push_back(*it);
	}
	++it;
      }

      boost::copy(quick_sortr(left, pred), std::back_inserter(sorted));
      sorted.push_back(pivot);
      boost::copy(quick_sortr(right, pred), std::back_inserter(sorted));
    }

    return sorted;
  }


  template <class Container, class Pred>
  Container quick_sorti(const Container &unsorted, Pred pred) {
    std::stack<Container> lsts;
    Container sorted;

    if (!unsorted.empty()) {
      lsts.push(unsorted);
      while (!lsts.empty()) {
	auto lst = lsts.top();
	lsts.pop();

	if (lst.size() == 1) {
	  sorted.push_back(lst[0]);
	  continue;
	}

	auto pivot = lst[0];

	Container left, right;
	auto it = std::begin(lst), last = std::end(lst);
	++it;
	while (it != last) {
	  if (pred(*it, pivot)) {
	    left.push_back(*it);
	  }
	  else {
	    right.push_back(*it);
	  }
	  ++it;
	}

	left.push_back(pivot);
	if (!right.empty()) {
	  lsts.push(right);
	}
	if (!left.empty()) {
	  lsts.push(left);
	}
      }
    }
    return sorted;
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
    auto sorted_teams = quick_sortr(teams, std::less<std::string>());
    boost::for_each(sorted_teams, [](const std::string &team) { std::cout << team << ", "; });
    std::cout << std::endl;
  }

  {
    auto sorted_teams = quick_sorti(teams, std::less<std::string>());
    boost::for_each(sorted_teams, [](const std::string &team) { std::cout << team << ", "; });
    std::cout << std::endl;
  }

  return 0;
}
