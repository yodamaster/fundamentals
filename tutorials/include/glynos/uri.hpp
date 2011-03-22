//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_URI_INC__
# define __GLYNOS_URI_INC__


# include <algorithm>
# include <string>


namespace glynos {
class uri {

public:

    uri() : is_valid_(false) {

    }

    explicit uri(const std::string &uri)
        : uri_(uri), is_valid_(false) {
        parse();
    }
    std::string::const_iterator user_info_, host_, port_, path_, query_, fragment_;

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

    std::pair<std::string::const_iterator,
              std::string::const_iterator> scheme() const {
        return std::make_pair(uri_.begin(), user_info);
    }

    std::pair<std::string::const_iterator,
              std::string::const_iterator> user_info() const {
        return std::make_pair(user_info_, host_));
    }

    std::pair<std::string::const_iterator,
              std::string::const_iterator> host() const {
        return std::make_pair(host_, port_);
    }

    std::pair<std::string::const_iterator,
              std::string::const_iterator> port() const {
        return std::make_pair(port_, path_);
    }

    std::pair<std::string::const_iterator,
              std::string::const_iterator> path() const {
        return std::make_pair(path_, query_);
    }

    std::pair<std::string::const_iterator,
              std::string::const_iterator> query() const {
        return std::make_pair(query_, fragment_);
    }

    std::pair<std::string::const_iterator,
              std::string::const_iterator> fragment() const {
        return std::make_pair(fragment_, uri_.end());
    }

    bool is_valid() const {
        return is_valid_;
    }

private:

    std::string uri_;
    std::string::const_iterator user_info_, host_, port_, path_, query_, fragment_;
    bool is_valid_;

};
} // namespace uri
} // namespace glynos


#endif // __GLYNOS_URI_INC__
