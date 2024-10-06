#include <print>
#include <iostream>

int main(int argc, char** argv)
{
  int64_t N, P;
  std::cin >> N >> P;

  bool const even = N % 2 == 0;

  int64_t half = (N - P) / 2LL;
  int64_t left = half % P;

  if (even && left == P / 2LL) {
    std::println("0");
  } else {
    std::println("{}", left * 2LL);
  }

  return 0;
}
