
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


namespace sandbox {
  typedef std::unordered_map<std::string, std::vector<std::string>> graph;

  template <class Graph>
  std::vector<typename Graph::key_type>
  find_path(const Graph &graph,
            typename Graph::key_type &start,
            typename Graph::key_type &end,
            std::vector<typename Graph::key_type> path = std::vector<typename Graph::key_type>()) {
    path.push_back(start);

    if (start == end) {
      return path;
    }

    auto it = graph.find(start);
    if (std::end(graph) == it) {
      return std::vector<typename Graph::key_type>();
    }

    std::vector<typename Graph::key_type> shortest;
    for (auto node : it->second) {
      if (std::find(std::begin(path), std::end(path), node) == std::end(path)) {
        auto new_path = find_shortest_path(graph, node, end, path);
        if (!new_path.empty()) {
          if (shortest.empty() || (new_path.size() < shortest.size())) {
            return new_path;
          }
        }
      }
    }
    return std::vector<typename Graph::key_type>();
  }

  template <class Graph>
  std::vector<typename Graph::key_type>
  find_shortest_path(const Graph &graph,
                     const typename Graph::key_type &start,
                     const typename Graph::key_type &end,
                     std::vector<typename Graph::key_type> path = std::vector<typename Graph::key_type>()) {
    path.push_back(start);

    if (start == end) {
      return path;
    }

    auto it = graph.find(start);
    if (std::end(graph) == it) {
      return std::vector<typename Graph::key_type>();
    }

    std::vector<typename Graph::key_type> shortest;
    for (auto node : it->second) {
      if (std::find(std::begin(path), std::end(path), node) == std::end(path)) {
        auto new_path = find_shortest_path(graph, node, end, path);
        if (!new_path.empty()) {
          if (shortest.empty() || (new_path.size() < shortest.size())) {
            shortest = new_path;
          }
        }
      }
    }
    return shortest;
  }
} // namespace sandbox


int main(int argc, char *argv[]) {
  sandbox::graph g;

  sandbox::graph::mapped_type a;
  a.push_back("B");
  a.push_back("C");
  g["A"] = a;

  sandbox::graph::mapped_type b;
  b.push_back("C");
  b.push_back("D");
  g["B"] = b;

  sandbox::graph::mapped_type c;
  c.push_back("D");
  g["C"] = c;

  sandbox::graph::mapped_type d;
  d.push_back("C");
  g["D"] = d;

  sandbox::graph::mapped_type e;
  e.push_back("F");
  g["E"] = e;

  sandbox::graph::mapped_type f;
  f.push_back("C");
  g["F"] = f;

  for (auto node : sandbox::find_path(g, std::string("A"), std::string("D"))) {
    std::cout << node << ", ";
  }
  std::cout << std::endl;

  for (auto node : sandbox::find_shortest_path(g, std::string("A"), std::string("D"))) {
    std::cout << node << ", ";
  }
  std::cout << std::endl;
}
