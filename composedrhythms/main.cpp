#include <print>
#include <iostream>
#include <cassert>

int main(int argc, char** argv)
{
  int N;
  std::cin >> N;

  int twos = N / 2;
  bool aThree = false;
  if (twos * 2 == N - 1) {
    twos--;
    aThree = true;
  }

  std::println("{}", twos + aThree);

  if (aThree) std::print("3{}", twos > 0 ? " " : "");

  for (int i = 0; i < twos; ++i) {
    std::print("2");
    if (i != twos - 1) std::print(" ");
  }

  std::println("");

  return 0;
}
