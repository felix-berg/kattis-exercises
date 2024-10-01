#include <print>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>

std::vector<int> computeSuffixRanks(std::string str) {
  int n = str.size();

  std::vector<std::vector<bool>> iLessThanj(n + 1, std::vector(n + 1, false));

  // if i = n, then xi...xn = Λ, so xi...xn < xj...xn for j < n
  for (int j = 0; j < n; ++j) {
    iLessThanj[n][j] = true;
  }
  // cases for j = n covered by constructor
  
  for (int i = n - 1; i >= 0; --i) {
    for (int j = n - 1; j >= 0; --j) {
      char xi = str[i], xj = str[j];
      // xi...xn < xj...xn for i, j < n iff
      //  xi == xj and x(i+1)...xn < x(j+1)...xn, or
      //  xi < xj 
      if (xi == xj) {
        iLessThanj[i][j] = iLessThanj[i + 1][j + 1];
      } else {
        iLessThanj[i][j] = xi < xj;
      }
    }
  }

  std::vector<int> counts(n), ranks(n);

  for (int i = 0; i < n; ++i) {
    ranks[i] = i;
    counts[i] = std::ranges::count(iLessThanj[i], 1);
  }

  std::ranges::sort(ranks, [&](int i, int j) {
    return counts[i] > counts[j];
  });

  return ranks;
}

struct Result {
  std::vector<int> nexts;
  std::vector<int> prevs;
};

Result doThing(std::string word) {
  Result result;
  result.nexts.resize(word.size());
  result.prevs.resize(word.size());



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
  for (auto [ word, qs ]: cases) {
    auto const ranks = computeSuffixRanks(word);
    for (int i = 0; i < qs.size(); ++i){
      std::print("{}", ranks[qs[i]]);
      if (i != qs.size() - 1) std::print(" ");
    }
    std::println("");
  }
  
  return 0;
}
