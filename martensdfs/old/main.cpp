#include <print>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ranges>

struct Edge {
  int f, t;
};

auto readInput() {
  struct {
    int nVertices;
    std::vector<Edge> edges;
    std::vector<int> path;
  } result;

  int nEdges;
  std::cin >> result.nVertices >> nEdges;
  
  result.edges.resize(nEdges);
  for (int i = 0; i < nEdges; ++i) {
    std::cin >> result.edges[i].f >> result.edges[i].t;
  }

  std::getchar();

  int i = 0;
  int c = 0;

  std::string s;
  std::getline(std::cin, s);

  std::istringstream iss { s }; 
  while (iss >> c) {
    result.path.push_back(c);
  }

  return result;
}

std::unordered_map<int, std::unordered_set<int>> createAdjacencyList(
  std::vector<Edge> const& edges, std::vector<int> const& path
) {
  std::unordered_map<int, std::unordered_set<int>> result;
  result.reserve(path.size());

  for (auto v: path) {
    result[v] = {};
  }

  for (auto [u, v]: edges) {
    result[u].insert(v);
    result[v].insert(u);
  }

  return result;
}

bool isValid(auto const& path, auto const& adjlist, int nVertices) {
  if (path.size() != nVertices)
    return false;

  int n = path.size();
  std::vector<bool> marked(n, false);

  for (int i = n - 1; i >= 0; --i) {
    int vi = path[i];

    bool consuming = true;
    for (int j = i + 1; j < n; ++j) {
      int vj = path[j];

      if (consuming) {
        if (!marked[j]) {
          if (adjlist.at(vi).contains(vj)) {
            marked[j] = true; // child of vi
          } else {
            consuming = false;
          }
        }
      } else {
        if (adjlist.at(vi).contains(vj)) {
            return false; // NIX
        }
      }
    }
  }

  for (int j = 1; j < n; ++j) {
    if (!marked[j]) {
      return false; // NIX
    }
  }

  return true;
}



int main(int argc, char** argv) {
  auto [ nVertices, edges, path ] = readInput();

  auto const whichVertices = path | std::ranges::to<std::unordered_set>();
  auto const adjlist = createAdjacencyList(edges, path);

  std::println("{}", isValid(path, adjlist, nVertices) ? "YES" : "NO");

  return 0;
}
