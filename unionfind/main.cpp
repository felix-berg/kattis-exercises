#include <print>
#include <ranges> 
#include <vector>

namespace sr = std::ranges;
namespace sv = std::ranges::views;

void linkRoots(int r1, int r2, auto&& parent, auto&& rank) {
  if (rank(r1) > rank(r2)) {
    parent(r2) = r1;
  } else {
    parent(r1) = r2;
    if (rank(r1) == rank(r2))
      rank(r2)++;
  }
}

int findRoot(int x, auto&& parent) {
  if (parent(x) == x) 
    return x;

  int r = findRoot(parent(x), parent);
  parent(x) = r;
  return r;
}

void unionSets(int x, int y, auto&& parent, auto&& rank) {
  return linkRoots(
    findRoot(x, parent), 
    findRoot(y, parent),
    parent, rank);
}

bool areInSameSet(int x, int y, auto&& parent) {
  return findRoot(x, parent) == findRoot(y, parent);
}

struct Query {
  char which;
  int x, y;
};

auto readInput() {
  struct {
    int n;
    std::vector<Query> queries;
  } result;

  int q;
  std::scanf("%d %d\n", &result.n, &q);

  result.queries.reserve(q);

  for (int i = 0; i < q; ++i) {
    char c;
    int x, y;
    std::scanf("%c %d %d\n", &c, &x, &y);
    result.queries.emplace_back(c, x, y);
  }
  
  return result;
}

int main(int argc, char** argv)
{
  auto [ n, queries ] = readInput();

  // make singleton sets for 0, 1, ..., n - 1
  std::vector parents = sv::iota(0, n) | sr::to<std::vector>();
  std::vector ranks = sv::repeat(0, n) | sr::to<std::vector>();

  auto const getParent = [&parents](int x) -> int& { return parents[x]; };
  auto const getRank = [&ranks](int x) -> int& { return ranks[x]; };

  for (auto [c, x, y]: queries) {
    switch (c) {
      case '?':
        std::println("{}", areInSameSet(x, y, getParent) ? "yes" : "no");
        break;
      case '=':
        unionSets(x, y, getParent, getRank);
        break;
      default: 
        break;
    }
  }

  return 0;
}
