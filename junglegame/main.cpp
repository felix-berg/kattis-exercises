#include <print>
#include <iostream>
#include <unordered_set>
#include <vector>

auto readInput() {
  struct {
    int N;
    std::vector<int> P, S;
  } result;

  std::cin >> result.N;

  result.P.resize(result.N);
  result.S.resize(result.N);
  
  for (int i = 0; i < result.N; ++i) {
    std::cin >> result.P[i] >> result.S[i];
  }

  return result;
}

int main(int argc, char** argv)
{
  auto [ N, P, S ] = readInput();

  using Cmp = decltype([](auto const& pair) {
    return (static_cast<int64_t>(pair.first) << 32) | static_cast<int64_t>(pair.second);
  });

  std::unordered_set<std::pair<int, int>, Cmp> crosses;
  std::unordered_set<std::pair<int, int>, Cmp> dots;

  crosses.reserve(N * N);
  dots.reserve(N * N);

  for (int i = 0; i < N; ++i) {
    crosses.insert(std::make_pair(P[i], S[i]));
  }

  std::vector<std::pair<int, int>> chosenVectors;
  chosenVectors.reserve(N);

  for (int p = 1; p <= N; ++p) {
    for (int s = 1; s <= N; ++s) {
      if (chosenVectors.size() >= N) goto STOP;

      if (dots.contains(std::make_pair(p, s))) continue;
      if (crosses.contains(std::make_pair(2 * p, 2 * s))) continue;

      // choose (p, s)
      chosenVectors.push_back(std::make_pair(p, s));
      for (auto [P, S]: crosses) {
        dots.insert(std::make_pair(P - p, S - s));
      }
    }
  }

STOP:

  if (chosenVectors.size() != N) {
    std::println("NO");
  } else {
    std::println("YES");
    for (auto [ p, s ]: chosenVectors) {
      std::println("{} {}", p, s);
    }
  }

  return 0;
}
