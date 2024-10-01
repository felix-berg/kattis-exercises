#include <cassert>
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

// assumes 0 <= x < path.size() for all x ∈ `path`
// returns adjacency list of graph where the vertex i has start time i
// in search according to `path` (so i is index in `path`)
std::vector<std::unordered_set<int>> createAdjacencyList(
  std::vector<Edge> const& edges, std::vector<int> const& path
) {
  std::vector<int> vertexToPathIndex(path.size());
  for (int i = 0; i < path.size(); ++i) {
    vertexToPathIndex[path[i]] = i;
  }

  std::vector<std::unordered_set<int>> adjlist(path.size(), std::unordered_set<int> {});
  for (auto const [u, v]: edges) {
    auto i = vertexToPathIndex[u],
         j = vertexToPathIndex[v];
    adjlist[i].insert(j);
    adjlist[j].insert(i); // undirected
  }

  return adjlist;
}


static constexpr int NO_INDEX = -1;

// create valid start time intervals [i, endIndices[i]) each node i ∈ {0...adjlist.size()}
std::vector<int> createDFSTree(std::vector<std::unordered_set<int>> const& adjlist) {
  int n = adjlist.size();
  std::vector<int> endIndices(adjlist.size(), NO_INDEX);

  std::vector<int> reverseRoots;
  reverseRoots.reserve(adjlist.size()); // would be worst case O(n) anyway

  for (int i = n - 1; i >= 0; --i) {
    int rootsToRemove = 0;
    // go through roots (in correct order)
    for (int j: reverseRoots | std::ranges::views::reverse) {
      if (adjlist[i].contains(j)) {
        rootsToRemove++;
      } else {
        break;
      }
    }
    
    reverseRoots.erase(reverseRoots.end() - rootsToRemove, reverseRoots.end());
    endIndices[i] = reverseRoots.empty() ? n : reverseRoots.back();
    reverseRoots.push_back(i); // why it is reversed :))
  }

  return endIndices;
}

bool validDFSTree(
  std::vector<int> const& endIndices, 
  std::vector<std::unordered_set<int>> const& adjlist
) {
  // invalid if not all in one tree, ie. interval of source is not [0, n),
  if (endIndices[0] != adjlist.size())
    return false;

  // invalid if any node has adjacency outside of its range
  for (int i = 0; i < adjlist.size(); ++i) {
    int maxStartTime = endIndices[i];
    for (int j: adjlist[i]) {
      if (j >= maxStartTime) {
        return false;
      }
    }
  }

  return true;
}

int main(int argc, char** argv) {
  auto [ nVertices, edges, path ] = readInput();

  if (path.size() != nVertices) {
    std::println("NO");
    return EXIT_SUCCESS;
  }

  auto const adjlist = createAdjacencyList(edges, path);
  auto const endIndices = createDFSTree(adjlist);
  
  std::println("{}", validDFSTree(endIndices, adjlist) ? "YES" : "NO");

  return 0;
}
