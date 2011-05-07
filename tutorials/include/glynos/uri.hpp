//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_URI_INC__
# define __BOOST_NETWORK_URI_INC__


# include <algorithm>
# include <pair>


namespace boost {
namespace network {
namespace uri {
template <
    class Tag
    >
class basic_uri {

public:

    typedef typename string<Tag>::type string_type;
    typedef typename string_type::const_iterator const_iterator_type;
    typedef std::pair<const_iterator_type, const_iterator_type> const_range_type;

    uri() : is_valid_(false) {

    }

    explicit uri(const string_type &uri)
        : uri_(uri), is_valid_(false) {
        parse();
    }

    uri(const uri &other)
        : uri_(other.uri_),
          user_info_(other.user_info_),
          host_(other.host_),
          port_(other.port_),
          path_(other.path_),
          query_(other.query_),
          fragment_(other.fragment_),
          is_valid_(other.is_valid_) {

    }

    uri &operator = (const uri &other) {
        uri(other).swap(*this);
        return *this;
    }

    ~uri() {

    }

    void swap(uri &other) {
        std::swap(uri_, other.uri_);
        std::swap(user_info_, other.user_info_);
        std::swap(host_, other.host_);
        std::swap(port_, other.port_);
        std::swap(path_, other.path_);
        std::swap(query_, other.query_);
        std::swap(fragment_, other.fragment_);
        std::swap(is_valid_, other.is_valid_);
    }

    const_range_type scheme_range() const {
        return std::make_pair(uri_.begin(), user_info);
    }

    const_range_type user_info_range() const {
        return std::make_pair(user_info_, host_);
    }

    const_range_type host_range() const {
        return std::make_pair(host_, port_);
    }

    const_range_type port_range() const {
        return std::make_pair(port_, path_);
    }

    const_range_type path_range() const {
        return std::make_pair(path_, query_);
    }

    const_range_type query_range() const {
        return std::make_pair(query_, fragment_);
    }

    const_range_type fragment_range() const {
        return std::make_pair(fragment_, uri_.end());
    }

    string_type scheme() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = scheme_range();
        return string_type(begin, end);
    }

    string_type user_info() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = user_info_range();
        return string_type(begin, end);
    }

    string_type host() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = host_range();
        return string_type(begin, end);
    }

    string_type port() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = port_range();
        return string_type(begin, end);
    }

    string_type path() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = path_range();
        return string_type(begin, end);
    }

    string_type query() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = query_range();
        return string_type(begin, end);
    }

    string_type fragment() const {
        const_iterator_type begin, end;
        boost::tie(begin, end) = fragment_range();
        return string_type(begin, end);
    }

    string_type to_string() const {
        return uri_;
    }

    bool is_valid() const {
        return is_valid_;
    }

private:

    void parse();

    string_type uri_;
    string_type::const_iterator user_info_, host_, port_, path_, query_, fragment_;
    bool is_valid_;

};
} // namespace uri
} // namespace network
} // namespace boost


# include "details/uri.hpp"


#endif // __BOOST_NETWORK_URI_INC__
