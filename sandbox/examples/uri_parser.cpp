// Copyright 2014 Glyn Matthews.

#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace sandbox {
struct uri_parts {
  std::string scheme, authority, user_info, host, port, path, query, fragment;
};

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

template <class InputIterator, class OutputIterator>
bool uri_parse(InputIterator first, InputIterator last, OutputIterator &out,
               uri_parts& parts) {
  parts.scheme.clear();
  parts.user_info.clear();
  parts.host.clear();
  parts.port.clear();
  parts.path.clear();
  parts.query.clear();
  parts.fragment.clear();

  auto state = uri_parser_state::start;
  auto hp_state = hierarchical_part_state::start;
  auto auth_state = authority_state::start;

  out = first;
  auto it = first;
  for (; it != last; ++it) {
    if (uri_parser_state::start == state) {
      state = uri_parser_state::scheme;
    }

    if (uri_parser_state::scheme == state) {
      if (*it == ':') {
        parts.scheme = std::string(out, it);
        state = uri_parser_state::colon;
      }
    }

    if (uri_parser_state::colon == state) {
      out = it;
      state = uri_parser_state::hierarchical_part;
      continue;
    }

    if (uri_parser_state::hierarchical_part == state) {
      if (hierarchical_part_state::start == hp_state) {
        if (*it == '/') {
          hp_state = hierarchical_part_state::slash_1;
          continue;
        }
        else {
          out = it;
          hp_state = hierarchical_part_state::path;
          continue;
        }
      }

      if (hierarchical_part_state::slash_1 == hp_state) {
        if (*it == '/') {
          hp_state = hierarchical_part_state::slash_2;
          continue;
        }
        else {
          return false;
        }
      }

      if (hierarchical_part_state::slash_2 == hp_state) {
        out = it;
        if (*it == '/') {
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
          if (*it == '@') {
            parts.user_info = std::string(out, it);
            auth_state = authority_state::at;
            continue;
          }
          else if (*it == ':') {
            // this is actually a host part, not a user_info
            parts.host = std::string(out, it);
            auth_state = authority_state::colon;
            continue;
          }
          else if (*it == '/') {
            // this is actually a host part, not a user_info
            parts.host = std::string(out, it);
            out = it;
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::path;
          }
          else if (*it == '?') {
            parts.host = std::string(out, it);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::question_mark;
            continue;
          }
          else if (*it == '#') {
            parts.host = std::string(out, it);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::hash;
            continue;
          }
        }

        if (authority_state::at == auth_state) {
          out = it;
          auth_state = authority_state::host;
          continue;
        }

        if (authority_state::host == auth_state) {
          if (*it == ':') {
            parts.host = std::string(out, it);
            auth_state = authority_state::colon;
            continue;
          }
          if (*it == '/') {
            parts.host = std::string(out, it);
            out = it;
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::path;
          }
        }

        if (authority_state::colon == auth_state) {
          out = it;
          auth_state = authority_state::port;
          continue;
        }

        if (authority_state::port == auth_state) {
          if (*it == '/') {
            parts.port = std::string(out, it);
            out = it;
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::path;
          }
          else if (*it == '?') {
            parts.port = std::string(out, it);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::question_mark;
            continue;
          }
          else if (*it == '#') {
            parts.port = std::string(out, it);
            auth_state = authority_state::finish;
            hp_state = hierarchical_part_state::finish;
            state = uri_parser_state::hash;
            continue;
          }
        }
      }

      if (hierarchical_part_state::path == hp_state) {
        if (*it == '?') {
          parts.path = std::string(out, it);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::question_mark;
          continue;
        }
        else if (*it == '#') {
          parts.path = std::string(out, it);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::hash;
          continue;
        }
      }

      if (hierarchical_part_state::finish == hp_state) {
        if (*it == '?') {
          parts.path = std::string(out, it);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::question_mark;
          continue;
        }
        else if (*it == '#') {
          parts.path = std::string(out, it);
          hp_state = hierarchical_part_state::finish;
          state = uri_parser_state::hash;
          continue;
        }
      }
    }

    if (uri_parser_state::question_mark == state) {
      out = it;
      state = uri_parser_state::query;
      continue;
    }

    if (uri_parser_state::query == state) {
      if (*it == '#') {
        parts.query = std::string(out, it);
        state = uri_parser_state::hash;
        continue;
      }
    }

    if (uri_parser_state::hash == state) {
      out = it;
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
    out = it;
    return false;
  }
  else if (uri_parser_state::hierarchical_part == state) {
    if ((hierarchical_part_state::start == hp_state) ||
        (hierarchical_part_state::slash_1 == hp_state) ||
        (hierarchical_part_state::slash_2 == hp_state)) {
      out = it;
      return false;
    }
    else if (hierarchical_part_state::authority == hp_state) {
      // this might be a host part, not a user_info
      if ((authority_state::user_info == auth_state) ||
          (authority_state::host == auth_state)) {
        parts.host = std::string(out, it);
        auth_state = authority_state::finish;
      }
    }
    else if (hierarchical_part_state::path == hp_state) {
      parts.path = std::string(out, it);
      hp_state = hierarchical_part_state::finish;
    }
    state = uri_parser_state::finish;
  }
  else if (uri_parser_state::query == state) {
    parts.query = std::string(out, it);
    state = uri_parser_state::finish;
  }
  else if (uri_parser_state::fragment == state) {
    parts.fragment = std::string(out, it);
    state = uri_parser_state::finish;
  }

  return true;
}

void parse_uri(const std::string &uri) {
  sandbox::uri_parts parts;
  std::string::const_iterator it;
  if (sandbox::uri_parse(std::begin(uri), std::end(uri), it, parts)) {
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
    std::copy(std::begin(uri), it, std::ostream_iterator<char>(std::cout));
    std::cout << "*";
    std::copy(it, std::end(uri), std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;
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
