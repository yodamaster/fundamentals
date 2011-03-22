
//             Copyright Glyn Matthews 2010, 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/spirit/home/phoenix.hpp>
#include <boost/regex.hpp>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <iterator>
#include <functional>
#include <iostream>


namespace sandbox {
std::vector<std::string> create_vec_str() {
    std::vector<std::string> vec_str;
    vec_str.push_back("Manchester United");
    vec_str.push_back("Liverpool");
    vec_str.push_back("Chelsea");
    vec_str.push_back("Aston Vanilla");
    vec_str.push_back("Arsenal");
    vec_str.push_back("Everton");
    vec_str.push_back("Wigan");
    vec_str.push_back("West Ham United");
    vec_str.push_back("Manchester City");
    vec_str.push_back("Sunderland");
    vec_str.push_back("Fulham");
    vec_str.push_back("Bolton Wanderers");
    vec_str.push_back("Hull");
    vec_str.push_back("Portsmouth");
    vec_str.push_back("Newcastle United");
    vec_str.push_back("Tottenham Hotspurs");
    vec_str.push_back("Stoke City");
    vec_str.push_back("Blackburn Rovers");
    vec_str.push_back("Middlesbrough");
    vec_str.push_back("West Bromwich Albion");
    return vec_str;
}


std::vector<int> create_vec_int_unsorted() {
    std::vector<int> vec_int;
    vec_int.push_back(2);
    vec_int.push_back(32);
    vec_int.push_back(43);
    vec_int.push_back(21);
    vec_int.push_back(12);
    vec_int.push_back(19);
    vec_int.push_back(38);
    vec_int.push_back(27);
    return vec_int;
}


template <
    class Rng
    >
struct in_t {
    const Rng &rng_;
    explicit in_t(const Rng &rng) :rng_(rng) {}
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
in_t<Rng>
in(const Rng &rng) {
    return in_t<Rng>(rng);
}


template <
    class Rng
    >
inline
typename boost::range_iterator<Rng>::type
midpoint(Rng &rng) {
    boost::function_requires<boost::RandomAccessRangeConcept<Rng> >();
    auto size = boost::end(rng) - boost::begin(rng);
    return boost::begin(rng) + size / 2;
}


template <
    class Rng
    >
inline
void
print_range(const Rng &rng, const char *name) {
    using boost::phoenix::arg_names::arg1;
    std::cout << " ++++ " << name << std::endl;
    boost::for_each(rng, std::cout << arg1 << ", ");
    std::cout << std::endl;
}
} // namespace sandbox


int
main(int argc, char *argv[]) {
    using boost::phoenix::bind;
    using boost::phoenix::arg_names::arg1;

    const std::string london_teams[] = { "Chelsea",
                                         "Arsenal",
                                         "Fulham",
                                         "Tottenham Hotspurs",
                                         "West Ham United" };

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
        // boost::transform(vec_str, std::back_inserter(list_str), arg1 + " FC");
        sandbox::print_range(list_str, "list_str");
    }

    {
        std::cout << " *** Test Generate ***" << std::endl;

        std::vector<double> vec_dbl(10);
        boost::generate(vec_dbl, &std::rand);
        boost::for_each(vec_dbl, arg1 /= INT_MAX);
        sandbox::print_range(vec_dbl, "vec_dbl");
        boost::sort(vec_dbl, std::less<double>());
        sandbox::print_range(vec_dbl, "vec_dbl");
    }

    {
        std::cout << " *** Test Counting Iterator ***" << std::endl;

        typedef boost::counting_iterator<int> Iter;
        sandbox::print_range(std::make_pair(Iter(1), Iter(7)), "counting_iterator");
    }

    {
        std::cout << " *** Test Push Back/Front ***" << std::endl;

        typedef boost::counting_iterator<int> Iter;
        std::vector<int> vec_int, vec_int_rev;
        boost::push_back(vec_int, std::make_pair(Iter(1), Iter(7)));
        sandbox::print_range(vec_int, "vec_int");
        boost::push_front(vec_int_rev, std::make_pair(Iter(1), Iter(7)));
        sandbox::print_range(vec_int_rev, "vec_int_rev");
    }

    {
        std::cout << " *** Test Erase ***" << std::endl;

        std::vector<double> vec_dbl(10);
        boost::generate(vec_dbl, &std::rand);
        boost::for_each(vec_dbl, arg1 /= INT_MAX);
        boost::remove_erase_if(vec_dbl, arg1 < .5);
        sandbox::print_range(vec_dbl, "vec_dbl");
    }

    {
        std::cout << " *** Test Replace ***" << std::endl;

        std::vector<std::string> vec_str(sandbox::create_vec_str());
        sandbox::print_range(vec_str, "vec_str");
        boost::replace_if(vec_str, arg1 == "Aston Vanilla", "Aston Villa");
        sandbox::print_range(vec_str, "vec_str");
    }

    {
        std::cout << " *** Test Find ***" << std::endl;

        // find Everton
        std::vector<std::string> vec_str(sandbox::create_vec_str());
        std::vector<std::string>::const_iterator it =
            boost::find(vec_str, "Everton");
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
                             | filtered(sandbox::in(london_teams)),
                             "London teams in top 6");

        sandbox::print_range(std::make_pair(boost::begin(league_table),
                                            sandbox::midpoint(league_table))
                             | filtered(sandbox::in(london_teams)),
                             "London teams in top half");

        sandbox::print_range(std::make_pair(sandbox::midpoint(league_table),
                                            boost::end(league_table))
                             | filtered(sandbox::in(london_teams)),
                             "London teams in bottom half");

        std::string s("New path to helicon part 1.");
        sandbox::print_range(s | tokenized("\\s+", -1), "Tokenized string");

        // std::vector<std::string> tokenized_s =
        //     boost::copy_range<std::vector<std::string> >(s | tokenized("\\s+", -1));
        // sandbox::print_range(boost::sort(tokenized_s), "Sorted tokenized string");
    }

    {
        std::cout << " *** Test toupper ***" << std::endl;

        std::string str = "come on the saints!";
        boost::for_each(str, arg1 = bind(::toupper, arg1));
        sandbox::print_range(str, "str");
    }

    return 0;
}
