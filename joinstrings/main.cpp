#include <limits>
#include <print>
#include <iostream>
#include <ranges>
#include <vector>

namespace sr = std::ranges;
namespace sv = sr::views;

using Query = std::pair<int, int>;

auto readInput() {
  struct {
    std::vector<std::string> words;
    std::vector<Query> queries;
  } result;

  int n;
  std::cin >> n;
  std::getchar();

  result.words.resize(n);
  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, result.words[i]);
  }
  
  result.queries.resize(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    auto& [ a, b ] = result.queries[i];
    std::scanf("%d %d\n", &a, &b);
    a--;
    b--;
  }

  return result;
}

static constexpr int NIL = std::numeric_limits<int>::max();
void combine(std::vector<int>& next, std::vector<int>& last, int a, int b) {
  next[last[a]] = b;
  next[last[b]] = a;
  last[a] = last[b];
  last[b] = NIL;
}

int main(int argc, char** argv)
{
  auto [ words, queries ] = readInput();

  // all have self loop
  auto next = sv::iota(0, (int) words.size()) | sr::to<std::vector>(),
       last = sv::iota(0, (int) words.size()) | sr::to<std::vector>();

  for (auto const& q: queries) {
    combine(next, last, q.first, q.second);
  }

  // will be one long list, the only 'last' entry will be end of the list
  int const end = *sr::find_if(last, [](int x) { return x != NIL; });
  int const head = next[end];

  int i = head;
  do {
    std::print("{}", words.at(i));
    i = next[i];
  } while (i != head);

  return 0;
}
