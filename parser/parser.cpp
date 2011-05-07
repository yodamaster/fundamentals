#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/spirit/repository/include/qi_iter_pos.hpp>
#include <iostream>


// parse date without copying

namespace qi = boost::spirit::qi;
namespace bf = boost::fusion;


typedef std::string::const_iterator iterator_type;
typedef boost::fusion::vector<iterator_type,
                              iterator_type,
                              iterator_type,
                              iterator_type,
                              iterator_type,
                              iterator_type> date_ranges;

template <
    typename Iterator
    >
struct date_grammar : qi::grammar<Iterator, date_ranges()> {
    date_grammar() : date_grammar::base_type(start, "date") {
        using boost::spirit::repository::qi::iter_pos;

         // we're only interested in the positions, so I ignore the
         // values themselves.
        start %=
            iter_pos >>
            qi::omit[*qi::digit] >>
            iter_pos >> '-' >> iter_pos >>
            qi::omit[*qi::digit] >>
            iter_pos >> '-' >> iter_pos >>
            qi::omit[*qi::digit] >>
            iter_pos
            ;
    }
    qi::rule<Iterator, date_ranges()> start;
};


void print(const std::string &d1, const std::string &d2, const std::string &d3) {
    std::cout << d3 << "/" << d2 << "/" << d1 << std::endl;
}

void print(const date_parts &date) {
    print(bf::at_c<0>(date), bf::at_c<1>(date), bf::at_c<2>(date));
}

void print(const date_ranges &date) {
    typedef boost::iterator_range<std::string::const_iterator> range_type;
    print(std::string(bf::at_c<0>(date), bf::at_c<1>(date)),
          std::string(bf::at_c<2>(date), bf::at_c<3>(date)),
          std::string(bf::at_c<4>(date), bf::at_c<5>(date)));
}


int
main(int argc, char *argv[]) {
    const std::string birthday = "1979-04-05";
    date_ranges d;
    date_grammar<std::string::const_iterator> date;
    std::string::const_iterator first = boost::begin(birthday);
    std::string::const_iterator last = boost::end(birthday);
    qi::parse(first, last, date, d);
    print(d);
    return 0;
}
