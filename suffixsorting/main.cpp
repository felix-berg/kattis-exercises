#include <print>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <ranges>

#include "rbtree.hpp"
using namespace fb::ds;

// whether xi...xn < xj...xn for i <= n, j <= n + 1 (where n = `str.size() - 1`)
bool iLessThanj(int i, int j, std::string const& str, auto&& getRank) {

  // if xj...xn = Λ, then xi...xn > xj...xn
  if (j >= str.size())
    return false;

  char xi = str[i], xj = str[j];

  if (xi < xj)
    return true;

  if (xj < xi)
    return false;
  
  // if xi == xj, then xi...xn < xj...xn iff x(i+1)..xn < x(j+1)...xn
  return getRank(i + 1) < getRank(j + 1);
}

template <typename Cmp, typename CalcAug>
int getTreeRank(AugRBTree<int, Cmp, int, CalcAug>& tree, int key) {
  size_t root = tree.root();
  size_t y = tree.find(key);
  if (y == tree::NIL) return 0;
  int rank = 1;
  while (y != root) {
    size_t par = tree.node(y).parent;
    if (tree.node(par).right == y) { // if y is right child
      size_t l = tree.node(par).left;
      rank += tree.augment(l) + 1; // add parent and left subtree
    }
    y = par;
  }

  return rank;
}

template <typename Cmp, typename CalcAug>
std::function<bool(int, int)> getComparisonFunction(
  AugRBTree<int, Cmp, int, CalcAug>& tree, std::string const& str
) {
  return [&tree, &str](int i, int j) {
    return iLessThanj(i, j, str, [&tree](int key) { return getTreeRank(tree, key); });
  };
}

std::function<void(AugmentArg<int, int>)> getComputeAugment() {
  return [](AugmentArg<int, int> arg) {
    int l = arg.left == nullptr ? 0 : *arg.left;
    int r = arg.right == nullptr ? 0 : *arg.right;
    arg.parent = 1 + l + r;
  };
}

std::vector<int64_t> computeSuffixRanks(std::string str) {
  // not actual rank, but we know that ranks[i] < ranks[j] iff xi...xn < xj...xn
  int n = str.size();

  using Cmp = std::function<bool(int, int)>;
  using CalcAug = std::function<void(AugmentArg<int, int>)>;

  // red-black tree of integers sorted by whether xi...xn < xj...xn
  SimpleRBTree<int, int> tree = createAugmentedRBTree(getComputeAugment(), getComparisonFunction(*tree, str));

  tree->insert(1);

  for (int i = n - 1; i >= 0; --i) {
    
  }

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
