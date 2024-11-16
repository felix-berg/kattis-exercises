#include <print>
#include <cassert>

using Grid = std::vector<std::vector<bool>>;

void simulateMove(Grid& grid, int fi, int fj, int ti, int tj) {
  assert(grid[fi][fj]);
  assert(!grid[ti][tj]);

  grid[fi][fj] = false;
  grid[ti][tj] = true;
}

void undoMove(Grid& grid, int fi, int fj, int ti, int tj) {
  assert(!grid[fi][fj]);
  assert(grid[ti][tj]);

  grid[fi][fj] = true;
  grid[ti][tj] = false;
}

int main(int argc, char** argv)
{
  std::println("Hello, world\n");
  return 0;
}
