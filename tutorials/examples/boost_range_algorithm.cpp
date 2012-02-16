//             Copyright Glyn Matthews 2010, 2011, 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptors.hpp>
#include <vector>
#include <string>
#include <list>
#include <functional>
#include <iostream>

namespace sandbox {
std::vector<std::string> create_vec_str() {
    return std::vector<std::string>{
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
}

std::vector<int> create_vec_int_unsorted() {
    return std::vector<int>{2, 32, 43, 21, 12, 19, 38, 27,};
}

template <
    class Rng
    >
struct is_member_of_t {
    const Rng &rng_;
    explicit is_member_of_t(const Rng &rng) :rng_(rng) {}
    template <
        class T
        >
    bool operator () (const T &value) const
    { return boost::end(rng_) != boost::find(rng_, value); }
};

template <
    class Rng
    >
inline
is_member_of_t<Rng>
is_member_of(const Rng &rng) {
    return is_member_of_t<Rng>(rng);
}

template <
    class Rng
    >
inline
typename boost::range_iterator<Rng>::type
midpoint(Rng &rng) {
    boost::function_requires<boost::RandomAccessRangeConcept<Rng>>();
    auto size = boost::end(rng) - boost::begin(rng);
    return boost::begin(rng) + size / 2;
}

template <
    class Rng
    >
inline
void
print_range(const Rng &rng, const char *name) {
    typedef typename Rng::value_type value_type;
    std::function<void (const value_type &)> print =
        [](const value_type &value){std::cout << value << ", ";};

    std::cout << " ++++ " << name << std::endl;
    boost::for_each(rng, print);
    std::cout << std::endl;
}

std::string add_fc(const std::string &name) {
     return name + " FC";
}
} // namespace sandbox

int
main(int argc, char *argv[]) {
    const auto london_teams =
        std::vector<std::string>{ "Arsenal",
                                  "Chelsea",
                                  "Fulham",
                                  "Queens Park Rangers",
                                  "Tottenham Hotspurs", };

    {
        std::cout << " *** Test Copy ***" << std::endl;

        std::vector<std::string> vec_str(sandbox::create_vec_str());
        std::list<std::string> list_str, list_str_rev;

        boost::copy(vec_str, std::back_inserter(list_str));
        sandbox::print_range(vec_str, "vec_str");
        sandbox::print_range(list_str, "list_str");
        boost::copy(vec_str, std::front_inserter(list_str_rev));
        sandbox::print_range(list_str_rev, "list_str_rev");
    }

    {
        std::cout << " *** Test Sort ***" << std::endl;

        std::vector<int> vec_int(sandbox::create_vec_int_unsorted());
        sandbox::print_range(vec_int, "vec_int");
        boost::sort(vec_int);
        sandbox::print_range(vec_int, "vec_int");
        boost::sort(vec_int, std::greater<int>());
        sandbox::print_range(vec_int, "vec_int");
    }

    {
        std::cout << " *** Test Transform ***" << std::endl;

        std::vector<std::string> vec_str(sandbox::create_vec_str());
        std::list<std::string> list_str;
        boost::transform(vec_str, std::back_inserter(list_str), [=](const std::string &team){return team + " FC";});
        sandbox::print_range(list_str, "list_str");
    }

    {
        std::cout << " *** Test Generate ***" << std::endl;

        std::vector<double> vec_dbl(10);
        boost::generate(vec_dbl, &std::rand);
        boost::for_each(vec_dbl, [](double &arg){arg /= INT_MAX;});
        sandbox::print_range(vec_dbl, "vec_dbl");
        boost::sort(vec_dbl, std::less<double>());
        sandbox::print_range(vec_dbl, "vec_dbl");
    }

    {
        std::cout << " *** Test Counting Iterator ***" << std::endl;

        sandbox::print_range(boost::counting_range(1, 7), "counting_iterator");
    }

    {
        std::cout << " *** Test Push Back/Front ***" << std::endl;

        std::vector<int> vec_int, vec_int_rev;
        boost::push_back(vec_int, boost::counting_range(1, 7));
        sandbox::print_range(vec_int, "vec_int");
        boost::push_front(vec_int_rev, boost::counting_range(1, 7));
        sandbox::print_range(vec_int_rev, "vec_int_rev");
    }

    {
        std::cout << " *** Test Erase ***" << std::endl;

        std::vector<double> vec_dbl(10);
        boost::generate(vec_dbl, &std::rand);
        boost::for_each(vec_dbl, [](double &arg){arg /= INT_MAX;});
        boost::remove_erase_if(vec_dbl, [](double arg){return arg < .5;});
        sandbox::print_range(vec_dbl, "vec_dbl");
    }

    {
        std::cout << " *** Test Replace ***" << std::endl;

        std::vector<std::string> vec_str(sandbox::create_vec_str());
        sandbox::print_range(vec_str, "vec_str");
        boost::replace_if(vec_str, [](const std::string &arg) { return arg  == "Aston Vanilla"; }, "Aston Villa");
        sandbox::print_range(vec_str, "vec_str");
    }

    {
        std::cout << " *** Test Find ***" << std::endl;

        // find Everton
        std::vector<std::string> vec_str(sandbox::create_vec_str());
        auto it = boost::find(vec_str, "Everton");
        if (it != vec_str.end()) {
            std::cout << " >>> found " << *it << std::endl;
        }

        // find the first team from London
        it = boost::find_first_of(vec_str, london_teams);
        if (it != vec_str.end()) {
            std::cout << " >>> found " << *it << std::endl;
        }
    }

    {
        std::cout << "*** Test Adaptors ***" << std::endl;
        using boost::adaptors::filtered;
        using boost::adaptors::tokenized;

        std::vector<std::string> league_table(sandbox::create_vec_str());
        sandbox::print_range(std::make_pair(boost::begin(league_table),
                                            boost::begin(league_table) + 6)
                             | filtered(sandbox::is_member_of(london_teams)),
                             "London teams in top 6");

        sandbox::print_range(std::make_pair(boost::begin(league_table),
                                            sandbox::midpoint(league_table))
                             | filtered(sandbox::is_member_of(london_teams)),
                             "London teams in top half");

        sandbox::print_range(std::make_pair(sandbox::midpoint(league_table),
                                            boost::end(league_table))
                             | filtered(sandbox::is_member_of(london_teams)),
                             "London teams in bottom half");

        std::string s("New path to helicon part 1.");
        sandbox::print_range(s | tokenized("\\s+", -1), "Tokenized string");
    }

    {
        std::cout << " *** Test toupper ***" << std::endl;

        std::string str = "come on the saints!";
        boost::for_each(str, [](char &c) {c = ::toupper(c);});
        std::cout << str << std::endl;
    }

    return 0;
}
