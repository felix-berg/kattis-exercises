#include <limits>
#include <print>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>
#include <set>
#include <algorithm>
#include <ranges>

struct RedBlackTree {

};

// whether xi...xn < xj...xn for i <= n, j <= n + 1 (where n = `str.size() - 1`)
bool iLessThanj(int i, int j, std::string const& str, std::vector<int64_t>& ranks) {

  // if xj...xn = Λ, then xi...xn > xj...xn
  if (j >= str.size())
    return false;

  char xi = str[i], xj = str[j];

  if (xi < xj)
    return true;

  if (xj < xi)
    return false;
  
  // if xi == xj, then xi...xn < xj...xn iff x(i+1)..xn < x(j+1)...xn
  return ranks[i + 1] < ranks[j + 1];
}

std::vector<int64_t> computeSuffixRanks(std::string str) {
  // not actual rank, but we know that ranks[i] < ranks[j] iff xi...xn < xj...xn
  std::vector<int64_t> ranks;

  int n = str.size();
  ranks.resize(n);

  auto const cmp = [&str, &ranks](int i, int j) {
    return iLessThanj(i, j, str, ranks);
  };
  
  // red-black tree of integers sorted by whether xi...xn < xj...xn
  std::set<int, decltype(cmp)> set { cmp };

  for (int i = n - 1; i >= 0; --i) {
    auto [ it, inserted ] = set.insert(i);
    assert(inserted);

    auto next = std::next(it);

    int64_t top = next == set.end() ? 
      std::numeric_limits<int64_t>::max() :
      ranks[*next];

    int64_t bot = it == set.begin() ? 
      0 : ranks[*std::prev(it)];

    // pick the middle value between the two neighbours in tree
    ranks[i] = bot + (top - bot) / 2;
  }

  return ranks;
}

auto readInput() {
  struct Case {
    std::string word;
    std::vector<int> qs;
  };

  std::vector<Case> cases;

  std::string numberLine;
  Case testCase;
  while (std::getline(std::cin, testCase.word)) {

    assert(std::getline(std::cin, numberLine)); 
    std::istringstream ss { numberLine };

    int n;
    ss >> n;
    testCase.qs.resize(n);

    for (int i = 0; i < n; ++i) {
      ss >> testCase.qs[i];
    }

    cases.push_back(testCase);
  }

  return cases;
}

int main(int argc, char** argv) {

  auto const cases = readInput();
  
  for (auto const& [ word, qs ]: cases) {
    auto const ranks = computeSuffixRanks(word);
    
    // list 0, 1, 2, 3, 4, ...
    std::vector<int> ithSuffix = 
      std::ranges::views::iota(0, (int) word.size()) | 
      std::ranges::to<std::vector>();

    // sort by ranks
    std::ranges::sort(ithSuffix, [&ranks](int i, int j) {
      return ranks[i] < ranks[j];
    });

    // answer queries
    for (int i = 0; i < qs.size(); ++i) {
      std::print("{}", ithSuffix[qs[i]]);
      if (i != qs.size() - 1) std::print(" ");
    }
    std::println("");
  }
  
  return 0;
}
