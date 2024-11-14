#include <print>
#include <iostream>
#include <cmath>

// Z[i] = number of 0's in xi...xn
// Q[i] = number of ?'s in xi...xn
// I[i] = number of inversions in xi...xn
//
// define Z[n + 1], Q[n + 1], I[n + 1] = 0


//        {     I[i + 1] + G(Z[i + 1], Q[i + 1])  if xi = '1'
// I[i] = {     I[i + 1]                          if xi = '0'
//        { 2 * I[i + 1] + G(Z[i + 1], Q[i + 1])  if xi = '?'
//

inline static constexpr int MOD = 1000000007;

int modAdd(int a, int b) {
  return (a + b) % MOD;
}

int modMultiply(int a, int b) {
  return (static_cast<int64_t>(a) * static_cast<int64_t>(b)) % MOD;
}

int modExponentiate(int base, int exp) {
  int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1)
      result = modMultiply(result, base);
    base = modMultiply(base, base);
    exp /= 2;
  }
  return result;
}

int intPow(int x, int p) {
  return static_cast<int>(std::pow(x, p));
}

// if string is 0?11?00?0 there are 2^3 different possible strings, each with
// min 4, max 7 zeroes (interval is [p, p + k])
//
// returns sum of number of zeroes in each possible string
//
// corresponds to number of inversions with the first 1
int sumOfZeroesInAll(int p, int k) {
  if (k == 0)
    return p;
  return modAdd(modMultiply(p, modExponentiate(2, k)), modExponentiate(2, k - 1));
}


int main(int argc, char** argv) {
  std::string str;
  std::getline(std::cin, str);

  int n = str.size();

  int Z = 0, Q = 0, I = 0;

  for (int i = n - 1; i >= 0; --i) {
    int zp = modAdd(Z, (str[i] == '0'));
    int qp = modAdd(Q, (str[i] == '?'));

    if (str[i] == '0') {
      /* nothing I' = I */
    } else if (str[i] == '1') {
      I = modAdd(I, sumOfZeroesInAll(Z, Q));
    } else if (str[i] == '?') {
      I = modAdd(modMultiply(2, I), sumOfZeroesInAll(Z, Q));
    }

    Z = zp;
    Q = qp;
  }

  std::println("{}", I);
  
  return 0;
}

//     0?11001?
// 00: 00110010 - 7 inversions
// 01: 00110011 - 4 inversions
// 10: 01110010 - 10 inversions
// 11: 01110011 - 6 inversions
//
// sum = 7 + 4 + 10 + 6 = 27
//
