#include <print>
#include <cassert>
#include <iostream>
#include <cmath>

uint64_t intPow(uint64_t base, uint64_t exp) {
  return std::powl(base, exp);
}

uint64_t flooredLogBase(uint64_t x, uint64_t b) {
  return std::log2l(x) / std::log2l(b);
}

uint64_t highestContainedTree(uint64_t k, uint64_t n) {
  return flooredLogBase(n * (k - 1) + 1, k);
}

uint64_t numInFullTree(uint64_t k, uint64_t h) {
  return (intPow(k, h) - 1) / (k - 1);
}

uint64_t numLeavesInFullTree(uint64_t k, uint64_t h) {
  return intPow(k, h - 1);
}

uint64_t numberOfOnes(uint64_t k, uint64_t n) {
  assert(n >= 0);
  if (n == 0) 
    return 0;

  // highest k-ary tree with <= n nodes
  uint64_t h = highestContainedTree(k, n);
  if (h >= k + 1) { // (if there are >= k internal nodes)
    return n - numLeavesInFullTree(k, k + 1);
  } else {
    uint64_t size = numInFullTree(k, h);
    int numTrees = n / size;
    uint64_t internalNodes = numTrees * (size - numLeavesInFullTree(k, h));
    return internalNodes + numberOfOnes(k, n % size);
  }
}

int main(int argc, char** argv) {
  uint64_t k, n;
  std::cin >> n >> k;
  std::println("{}", numberOfOnes(k, n));
  return 0;
}              

// biggest tree with k = 3 before nick gets addicted 💀
// string 'walks' in post-order (right, left, root)
//                  1
//            /     |     \
//      1           1           1
//    / | \       / | \       / | \
//   /  |  \     /  |  \     /  |  \
//  1   1   1   1   1   1   1   1   1
//  |   |   |   |   |   |   |   |   |
// 000 000 000 000 000 000 000 000 000 
