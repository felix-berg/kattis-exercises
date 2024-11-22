#include <print>
#include <iostream>
#include <deque>

void forEachCommand(auto&& func) {
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::string cmd;
    int index;

    std::cin >> cmd >> index;
    func(cmd, index);
  }
}

int main(int argc, char** argv)
{
  std::deque<int> first, second;

  auto const fixup = [&] {
    while (true) {
      if (first.size() < second.size()) {
        int x = second.front(); second.pop_front();
        first.push_back(x);
      } else if (first.size() > second.size() + 1) {
        int x = first.back(); first.pop_back();
        second.push_front(x);
      } else {
        // now XXXXX XXXX
        // or  XXXXX XXXXX
        break;
      }
    }
  };

  forEachCommand([&](auto cmd, int i) {
    if (cmd == "get") {
      std::println("{}", 
        i < first.size() ? first.at(i) : second.at(i - first.size())
      );
    } else if (cmd == "push_front") {
      first.push_front(i);
    } else if (cmd == "push_back") {
      second.push_back(i);
    } else if (cmd == "push_middle") {
      first.push_back(i);
    } else {
      exit(1);
    }

    fixup();
  });

  return 0;
}
