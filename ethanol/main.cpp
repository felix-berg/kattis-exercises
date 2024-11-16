#include <print>

int main(int argc, char** argv)
{
  int n;
  std::scanf("%d", &n);


  std::print(" ");
  for (int i = 0; i < n; ++i) {
    std::print(" H");
  }
  std::println(" ");

  std::print(" ");
  for (int i = 0; i < n; ++i) {
    std::print(" |");
  }
  std::println(" ");

  std::print("H-");
  for (int i = 0; i < n; ++i) {
    std::print("C-");
  }
  std::println("OH");

  std::print(" ");
  for (int i = 0; i < n; ++i) {
    std::print(" |");
  }
  std::println(" ");

  std::print(" ");
  for (int i = 0; i < n; ++i) {
    std::print(" H");
  }
  std::println(" ");
  

  return 0;
}
