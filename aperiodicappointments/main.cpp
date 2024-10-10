#include <print>
#include <iostream>
#include <unordered_map>
#include <cmath>

int intPow(int n, int e) {
  return static_cast<int>(std::pow(n, e));
}

int nodesInFullKAryTree(int k, int h) {
  return (intPow(k, h) - 1) / (k - 1);
}

int64_t hashPair(int a, int b) {
  return static_cast<int64_t>(a) << 31 | static_cast<int64_t>(b);
}

int maxTreeKAryTreeHeightInN(int k, int n) {
  static std::unordered_map<int64_t, int> memo;

  int64_t p = hashPair(k, n);
  if (memo.contains(p))
    return memo.at(p);

  int h = 1;
  while (nodesInFullKAryTree(k, h) <= n) 
    h++;
  memo[p] = h - 1;
  return h - 1;
}

int numInternalNodes(int k, int h) {
  return nodesInFullKAryTree(k, h) - intPow(k, h - 1);
}

int numOnes(int k, int n) {
  if (n <= k) return 0;

  static std::unordered_map<int64_t, int> memo;
  int64_t p = hashPair(k, n);
  if (memo.contains(p))
    return memo.at(p);

  // find height of max tree that we can 'pack' into n
  int maxHeight = maxTreeKAryTreeHeightInN(k, n);
  int answ;
  if (maxHeight <= k) { // if there are < maxHeight internal layers
    // nick is not addicted to doctor yet
    int numIntNodes = numInternalNodes(k, maxHeight);
    int numLeft = n - nodesInFullKAryTree(k, maxHeight);
    
    answ = numIntNodes + numOnes(k, numLeft);
  } else {
    // nick is addicted to docor 💀💀💀
    int numIntNodes = numInternalNodes(k, k + 1);
    int rest = n - nodesInFullKAryTree(k, k + 1); // rest are 1's
    answ = numIntNodes + rest;
  }
  memo[p] = answ;
  return answ;
}

int main(int argc, char** argv)
{
  int k, n;
  std::cin >> n >> k;

  std::println("{}", numOnes(k, n));

  return 0;
}
