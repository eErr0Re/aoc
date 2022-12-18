#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    int x, y, z;
    char c;

    const unsigned size {50};

    std::vector<std::vector<std::vector<bool>>> grid(size, std::vector<std::vector<bool>>(size, std::vector<bool>(size, false)));
    unsigned sides {};

    while (in >> x >> c >> y >> c >> z)
    {
        sides += 6;
        grid[x][y][z] = true;

        if (x - 1 >= 0 && grid[x - 1][y][z])
            sides -= 2;

        if (x + 1 < size && grid[x + 1][y][z])
            sides -= 2;

        if (y - 1 >= 0 && grid[x][y - 1][z])
            sides -= 2;

        if (y + 1 < size && grid[x][y + 1][z])
            sides -= 2;

        if (z - 1 >= 0 && grid[x][y][z - 1])
            sides -= 2;

        if (z + 1 < size && grid[x][y][z + 1])
            sides -= 2;
    }

    std::cout << sides << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
