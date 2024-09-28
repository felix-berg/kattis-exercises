#include <iostream>
#include <print>
#include <vector>
#include <utility>

template <typename T>
using Grid = std::vector<std::vector<T>>;

template <typename T>
Grid<T> clearGrid(T&& elm, int rows, int cols) {
  return std::vector(rows, std::vector(cols, elm));
}

auto readInput() {
  struct {
    int m, n;
    std::vector<std::vector<bool>> grid;
  } result;

  std::cin >> result.n >> result.m;
  result.grid = clearGrid(false, result.n, result.m);
  
  for (int i = 0; i < result.n; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < result.m; ++j) {
      result.grid[i][j] = s[j] == '1';
    }
  }

  return result;
}

int outOfBounds(int i, int j, int n, int m) {
 return i < 0 || i >= n || j < 0 || j >= m;
}

void dfsVisit(Grid<bool> const& grid, Grid<bool>& visited, Grid<bool>& connectsToSea, int i, int j, int n, int m) {
  if (outOfBounds(i, j, n, m) || visited[i][j] || grid[i][j]) // don't visit land
    return;

  visited[i][j] = true;
  connectsToSea[i][j] = true;

  auto&& neighbours = {
    std::make_pair(i - 1, j),
    std::make_pair(i + 1, j),
    std::make_pair(i, j - 1),
    std::make_pair(i, j + 1)
  };
  
  for (auto const [ii, jj]: neighbours)
    dfsVisit(grid, visited, connectsToSea, ii, jj, n, m);
}

int main(int argc, char** argv) {
  auto [ m, n, grid ] = readInput();

  Grid<bool> visited = clearGrid(false, n, m), 
             connectsToSea = clearGrid(false, n, m);
  
  for (int i = 0; i < n; ++i) {
    // left edge
    dfsVisit(grid, visited, connectsToSea, i, 0, n, m);
    // right edge
    dfsVisit(grid, visited, connectsToSea, i, m - 1, n, m);
  }
  
  for (int j = 0; j < m; ++j) {
    // top edge
    dfsVisit(grid, visited, connectsToSea, 0, j, n, m);
    // bottom edge
    dfsVisit(grid, visited, connectsToSea, n - 1, j, n, m);
  }

  auto const numLandNeighbours = [&grid, &m, &n](int i, int j) {
    auto&& neighbours = {
      std::make_pair(i - 1, j),
      std::make_pair(i + 1, j),
      std::make_pair(i, j - 1),
      std::make_pair(i, j + 1)
    };
    int s = 0;
    for (auto [ii, jj]: neighbours) {
      s += !outOfBounds(ii, jj, n, m) && grid[ii][jj];
    }
    return s;
  };

  int coastLength = 0;
  for (int i = -1; i < n + 1; ++i) {
    for (int j = -1; j < m + 1; ++j) {
      if (outOfBounds(i, j, n, m) || connectsToSea[i][j]) {
        coastLength += numLandNeighbours(i, j);
      }
    }
  }

  std::println("{}", coastLength);
  
  return 0;
}
