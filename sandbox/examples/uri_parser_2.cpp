// Copyright 2014 Glyn Matthews.

#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <boost/utility/string_ref.hpp>
#include <boost/optional.hpp>
#include <iostream>

namespace sandbox {
typedef boost::optional<boost::string_ref> uri_part;

struct uri_parts {
  uri_part scheme, authority, user_info, host, port, path, query, fragment;
};

inline
std::ostream& operator << (std::ostream& os, const uri_part& part) {
  if (part) {
    std::copy(part->begin(), part->end(), std::ostream_iterator<char>(os));
  }
  return os;
}

enum class uri_parser_state {
  start,
  scheme,
  colon,
  hierarchical_part,
  question_mark,
  query,
  hash,
  fragment,
  finish,
};

enum class hierarchical_part_state {
  start,
  slash_1,
  slash_2,
  authority,
  path,
  finish,
};

enum class authority_state {
  start,
  user_info,
  at,
  host,
  colon,
  port,
  finish,
};

bool uri_parse(const char *input, std::size_t size, std::size_t& parsed_until, uri_parts& parts) {
  parsed_until = 0;
  parts.scheme = boost::none;
  parts.user_info = boost::none;
  parts.host = boost::none;
  parts.port = boost::none;
  parts.path = boost::none;
  parts.query = boost::none;
  parts.fragment = boost::none;

  auto state = uri_parser_state::start;
  auto hp_state = hierarchical_part_state::start;
  auto auth_state = authority_state::start;

  std::size_t i = 0;
  for (; i < size; ++i) {
    if (uri_parser_state::start == state) {
      state = uri_parser_state::scheme;
    }

    if (uri_parser_state::scheme == state) {
      if (input[i] == ':') {
        // parts.scheme = std::string(out, it);
        parts.scheme = boost::string_ref(&input[parsed_until], i - parsed_until);
        state = uri_parser_state::colon;
      }
    }

    if (uri_parser_state::colon == state) {
      parsed_until = i;
      state = uri_parser_state::hierarchical_part;
      continue;
    }

    if (uri_parser_state::hierarchical_part == state) {
      if (hierarchical_part_state::start == hp_state) {
        if (input[i] == '/') {
          hp_state = hierarchical_part_state::slash_1;
          continue;
        }
        else {
          parsed_until = i;
          hp_state = hierarchical_part_state::path;
          continue;
        }
      }

      if (hierarchical_part_state::slash_1 == hp_state) {
        if (input[i] == '/') {
          hp_state = hierarchical_part_state::slash_2;
          continue;
        }
        else {
          return false;
        }
      }

      if (hierarchical_part_state::slash_2 == hp_state) {
        parsed_until = i;
        if (input[i] == '/') {
          hp_state = hierarchical_part_state::path;
        }
        else {
          hp_state = hierarchical_part_state::authority;
        }
      }

      if (hierarchical_part_state::authority == hp_state) {
        if (authority_state::start == auth_state) {
          auth_state = authority_state::user_info;
          continue;
        }

        if (authority_state::user_info == auth_state) {
          if (input[i] == '@') {
            parts.user_info = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::at;
            continue;
          }
          else if (input[i] == ':') {
            // this is actually a host part, not a user_info
            parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::colon;
            continue;
          }
          else if (input[i] == '/') {
            // this is actually a host part, not a user_info
            parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
            parsed_until = i;
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::path;
          }
          else if (input[i] == '?') {
            parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::question_mark;
            continue;
          }
          else if (input[i] == '#') {
            parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::hash;
            continue;
          }
        }

        if (authority_state::at == auth_state) {
          parsed_until = i;
          auth_state = authority_state::host;
          continue;
        }

        if (authority_state::host == auth_state) {
          if (input[i] == ':') {
            parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::colon;
            continue;
          }
          if (input[i] == '/') {
            parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
            parsed_until = i;
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::path;
          }
        }

        if (authority_state::colon == auth_state) {
          parsed_until = i;
          auth_state = authority_state::port;
          continue;
        }

        if (authority_state::port == auth_state) {
          if (input[i] == '/') {
            parts.port = boost::string_ref(&input[parsed_until], i - parsed_until);
            parsed_until = i;
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::path;
          }
          else if (input[i] == '?') {
            parts.port = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::question_mark;
            continue;
          }
          else if (input[i] == '#') {
            parts.port = boost::string_ref(&input[parsed_until], i - parsed_until);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::hash;
            continue;
          }
        }
      }

      if (hierarchical_part_state::path == hp_state) {
        if (input[i] == '?') {
          parts.path = boost::string_ref(&input[parsed_until], i - parsed_until);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::question_mark;
          continue;
        }
        else if (input[i] == '#') {
          parts.path = boost::string_ref(&input[parsed_until], i - parsed_until);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::hash;
          continue;
        }
      }

      if (hierarchical_part_state::finish == hp_state) {
        if (input[i] == '?') {
          parts.path = boost::string_ref(&input[parsed_until], i - parsed_until);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::question_mark;
          continue;
        }
        else if (input[i] == '#') {
          parts.path = boost::string_ref(&input[parsed_until], i - parsed_until);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::hash;
          continue;
        }
      }
    }

    if (uri_parser_state::question_mark == state) {
      parsed_until = i;
      state = uri_parser_state::query;
      continue;
    }

    if (uri_parser_state::query == state) {
      if (input[i] == '#') {
        parts.query = boost::string_ref(&input[parsed_until], i - parsed_until);
        state = uri_parser_state::hash;
        continue;
      }
    }

    if (uri_parser_state::hash == state) {
      parsed_until = i;
      state = uri_parser_state::fragment;
      continue;
    }
  }

  if (uri_parser_state::start == state) {
    // The URI is empty, but still valid.
    state = uri_parser_state::finish;
    hp_state = hierarchical_part_state::finish;
    auth_state = authority_state::finish;
  }
  else if ((uri_parser_state::scheme == state) ||
           (uri_parser_state::colon == state)) {
    parsed_until = i;
    return false;
  }
  else if (uri_parser_state::hierarchical_part == state) {
    if ((hierarchical_part_state::start == hp_state) ||
        (hierarchical_part_state::slash_1 == hp_state) ||
        (hierarchical_part_state::slash_2 == hp_state)) {
      parsed_until = i;
      return false;
    }
    else if (hierarchical_part_state::authority == hp_state) {
      // this might be a host part, not a user_info
      if ((authority_state::user_info == auth_state) ||
          (authority_state::host == auth_state)) {
        parts.host = boost::string_ref(&input[parsed_until], i - parsed_until);
        auth_state = authority_state::finish;
      }
    }
    else if (hierarchical_part_state::path == hp_state) {
      parts.path = boost::string_ref(&input[parsed_until], i - parsed_until);
      hp_state = hierarchical_part_state::finish;
    }
    state = uri_parser_state::finish;
  }
  else if (uri_parser_state::query == state) {
    parts.query = boost::string_ref(&input[parsed_until], i - parsed_until);
    state = uri_parser_state::finish;
  }
  else if (uri_parser_state::fragment == state) {
    parts.fragment = boost::string_ref(&input[parsed_until], i - parsed_until);
    state = uri_parser_state::finish;
  }

  return true;
}

void parse_uri(const std::string &uri) {
  sandbox::uri_parts parts;
  std::size_t distance = 0;
  if (sandbox::uri_parse(uri.c_str(), uri.size(), distance, parts)) {
    std::cout << "'" << uri << "' is a valid URI." << std::endl;
    std::cout << " " << parts.scheme << std::endl;
    std::cout << " " << parts.user_info << std::endl;
    std::cout << " " << parts.host << std::endl;
    std::cout << " " << parts.port << std::endl;
    std::cout << " " << parts.path << std::endl;
    std::cout << " " << parts.query << std::endl;
    std::cout << " " << parts.fragment << std::endl;
  }
  else {
    std::cout << "'" << uri << "' is an invalid URI." << std::endl;
    //std::copy(std::begin(uri), it, std::ostream_iterator<char>(std::cout));
    //std::cout << "*";
    //std::copy(it, std::end(uri), std::ostream_iterator<char>(std::cout));
    //std::cout << std::endl;
  }
  std::cout << "-------------------------------------------" << std::endl;
}
} // namespace sandbox

int main(int argc, char* argv[]) {
  sandbox::parse_uri("ftp://user_info@example.com:8000/path/?query#fragment");
  sandbox::parse_uri("ftp://user_info@example.com/path/?query#fragment");
  sandbox::parse_uri("http://example.com");
  sandbox::parse_uri("http://example.com/");
  sandbox::parse_uri("http://example.com:8000/");
  sandbox::parse_uri("http://example.com/?query");
  sandbox::parse_uri("http://example.com/#fragment");
  sandbox::parse_uri("mailto:user_info@example.com?query#fragment");
  sandbox::parse_uri("file:///home/example/.bashrc");
  sandbox::parse_uri("http://example.com?query");
  sandbox::parse_uri("http://example.com#fragment");
  sandbox::parse_uri("file:///home/example/.bashrc?query#fragment");
  sandbox::parse_uri("file:///home/example/.bashrc?query");
  sandbox::parse_uri("file:///home/example/.bashrc#fragment");
  sandbox::parse_uri("");

  sandbox::parse_uri("scheme");
  sandbox::parse_uri("scheme:");
  return 0;
}
