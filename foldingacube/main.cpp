#include <print>
#include <utility>
#include <cassert>
#include <array>
#include <algorithm>

namespace sr = std::ranges;

enum class Direction {
    BOTTOM, TOP, NORTH, EAST, SOUTH, WEST,
    NUM_DIRECTIONS
};

Direction oppositeDirection(Direction dir) {
  using enum Direction;
  switch (dir) {
  case BOTTOM: return TOP;
  case TOP:    return BOTTOM;
  case NORTH:  return SOUTH;
  case EAST:   return WEST;
  case SOUTH:  return NORTH;
  case WEST:   return EAST;
  default: std::unreachable();
  }
}

using Cube = std::array<int, std::to_underlying(Direction::NUM_DIRECTIONS)>;

int& cubeAt(Cube& cube, Direction at) {
  return cube.at(std::to_underlying(at));
}

Cube rotate(Cube cube, Direction around) {
  using enum Direction;
  assert(around != TOP && around != BOTTOM);

  Cube result {};
  auto const setTo = [&cube, &result](Direction dst, Direction src) {
    cubeAt(result, dst) = cubeAt(cube, src);
  };

  switch (around) {
  case NORTH:
    setTo(BOTTOM, NORTH);
    setTo(TOP, SOUTH);
    setTo(EAST, EAST);
    setTo(WEST, WEST);
    setTo(NORTH, TOP);
    setTo(SOUTH, BOTTOM);
    break;

  case EAST:
    setTo(BOTTOM, EAST);
    setTo(TOP, WEST);
    setTo(EAST, TOP);
    setTo(WEST, BOTTOM);
    setTo(NORTH, NORTH);
    setTo(SOUTH, SOUTH);
    break;

  case SOUTH:
    setTo(BOTTOM, SOUTH);
    setTo(TOP, NORTH);
    setTo(EAST, EAST);
    setTo(WEST, WEST);
    setTo(NORTH, BOTTOM);
    setTo(SOUTH, TOP);
    break;

  case WEST:
    setTo(BOTTOM, WEST);
    setTo(TOP, EAST);
    setTo(EAST, BOTTOM);
    setTo(WEST, TOP);
    setTo(NORTH, NORTH);
    setTo(SOUTH, SOUTH);
    break;

  default: std::unreachable();
  }

  return result;
}

void rotateInPlace(Cube& cube, Direction dir) {
  cube = rotate(cube, dir);
}

using BoolGrid = std::array<std::array<bool, 6>, 6>;

BoolGrid readInput() {
  std::array<std::array<bool, 6>, 6> result {}; 
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      char c = std::getchar();
      result[i][j] = c == '#';
    }
    std::getchar(); // ignore newline
  }
  return result;
}

void dfsVisit(BoolGrid const& grid, BoolGrid& visited, Cube& cube, int i, int j) {
  assert(0 <= i && j < 6 && 0 <= j && j < 6); 
  assert(grid[i][j]);

  using enum Direction;

  visited[i][j] = true;
  cubeAt(cube, BOTTOM) += 1; 

  std::array neighbours {
    std::tuple(SOUTH, i + 1, j),
    std::tuple(NORTH, i - 1, j),
    std::tuple(EAST,  i, j + 1),
    std::tuple(WEST,  i, j - 1)
  };

  auto const shouldVisit = [&grid, &visited](int ii, int jj) {
    return ii >= 0 && ii < 6 && jj >= 0 && jj < 6 && grid[ii][jj] && !visited[ii][jj];
  };
  
  for (auto [ dir, ii, jj ]: neighbours) {
    if (!shouldVisit(ii, jj)) 
      continue;
  
    rotateInPlace(cube, dir);
    dfsVisit(grid, visited, cube, ii, jj);
    rotateInPlace(cube, oppositeDirection(dir));
  }
}

std::pair<int, int> findStartPos(BoolGrid const& grid) {
  for (int r = 0; r < grid.size(); ++r) {
    for (int c = 0; c < grid[r].size(); ++c) {
      if (grid[r][c])
        return std::make_pair(r, c);
    }
  }
  std::exit(1); // would break assumption
}

int main(int argc, char** argv)
{
  auto grid = readInput();

  using enum Direction;
  BoolGrid visited {};
  Cube cube {};

  auto [ starti, startj ] = findStartPos(grid);
  dfsVisit(grid, visited, cube, starti, startj);

  bool const invalidSideExists = sr::find_if(cube, [](int i) { return i != 1; }) != cube.end();
  std::println("{}", invalidSideExists ? "cannot fold" : "can fold");
  return 0;
}
