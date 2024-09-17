#include <print>
#include <vector>
#include <iostream>
#include <utility>

struct Path {
    std::pair<int, int> from, to;
};

auto readInput() {
    struct {
        int cols, rows;
        std::vector<std::vector<bool>> field;
        std::vector<Path> paths;
    } result;

    std::cin >> result.cols >> result.rows;
    result.field.resize(result.rows);
    for (int i = 0; i < result.rows; ++i) {
        result.field[i].resize(result.cols);
    }

    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            int b;
            std::cin >> b;
            result.field[i][j] = b == 1;
        }
    }

    int n;
    std::cin >> n;
    result.paths.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> result.paths[i].from.first;
        std::cin >> result.paths[i].from.second;
        std::cin >> result.paths[i].to.first;
        std::cin >> result.paths[i].to.second;
    }

    return result;
}

int main(int argc, char** argv)
{
    std::println("Hello, world!\n");

    auto [ rows, cols, field, paths ] = readInput();

    return 0;
}
