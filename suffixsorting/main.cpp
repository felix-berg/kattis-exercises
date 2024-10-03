#include <print>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

// whether xi...xn < xj...xn for i <= n, j <= n + 1 (where n = `str.size() - 1`)
bool iLessThanj(int i, int j, std::string const& str, std::vector<int>& ranks) {
  assert(i < str.size());

  // if xj...xn = Λ, then xi...xn > xj...xn
  if (j >= str.size())
    return false;

  char xi = str[i], 
       xj = str[j];

  // if xi < xj, then xi...xn < xj...xn
  if (xi < xj) {
    return true;
  }

  // if xi > xj, then xi...xn > xj...xn
  if (xj < xi) {
    return false;
  }

  // if xi == xj, then xi...xn < xj...xn iff x(i+1)..xn < x(j+1)...xn
  return iLessThanj(i + 1, j + 1, str, ranks);
}

std::vector<int> const& computeSuffixRanks(std::string str) {
  static std::vector<int> ranks;

  int n = str.size();
  ranks.resize(n);

  for (int i = n - 1; i >= 0; --i) {
    char xi = str[i];
    
    ranks[i] = n - i - 1; // assume last rank
    
    // compute rank of xi...xn
    for (int j = i + 1; j < n; ++j) {
      if (iLessThanj(i, j, str, ranks)) {
        ranks[i]--; // beats xj...xn
        ranks[j]++; // j is not looked at again, so we can update now
      }
    }
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
    auto const& ranks = computeSuffixRanks(word);

    std::vector<int> ithSuffix(ranks.size());
    for (int i = 0; i < ranks.size(); ++i)
      ithSuffix[ranks[i]] = i;
    
    for (int i = 0; i < qs.size(); ++i) {
      std::print("{}", ithSuffix[qs[i]]);
      if (i != qs.size() - 1) std::print(" ");
    }

    std::println("");
  }
  
  return 0;
}
