#include <print>
#include <iostream>
#include <cassert>
#include <vector>

struct Point { int x, y; };

auto readInput() {
  struct {
    Point from, to;
    Point clue;
  } result;

  std::cin >> result.from.x >> result.from.y;
  std::cin >> result.to.x >> result.to.y;
  std::cin >> result.clue.x >> result.clue.y;

  return result;
}

static constexpr int INFTY = 100000000;

std::vector<Point> createPath(Point from, Point to, Point clue) {
  assert(from.x <= to.x && from.y <= to.y);

  if (clue.x <= to.x && clue.y >= from.y) {
    return {
      { from.x, -INFTY }, 
      { INFTY, -INFTY },
      { INFTY, to.y }
    };
  }

  if (clue.x >= from.x && clue.y <= to.y) {
    return {
      { -INFTY, from.y },
      { -INFTY, INFTY },
      { to.x, INFTY }
    };
  }

  return {};
}


int main(int argc, char** argv)
{
  auto [ from, to, clue ] = readInput();

  const bool flipx = from.x > to.x;
  const bool flipy = from.y > to.y;

  if (flipx) {
    from.x *= -1;
    to.x *= -1;
    clue.x *= -1;
  }

  if (flipy) {
    from.y *= -1;
    to.y *= -1;
    clue.y *= -1;
  }

  auto path = createPath(from, to, clue);

  std::println("{}", path.size());
  for (auto& pnt: path) {
    pnt.x *= (2 * !flipx - 1);
    pnt.y *= (2 * !flipy - 1);
    std::println("{} {}", pnt.x, pnt.y);
  }

  return 0;
}
