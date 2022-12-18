#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

const unsigned size {50};

unsigned min_x {size}, max_x {};
unsigned min_y {size}, max_y {};
unsigned min_z {size}, max_z {};

std::vector<std::vector<std::vector<char>>> grid(size, std::vector<std::vector<char>>(size, std::vector<char>(size, '.')));

int explore(int x, int y, int z)
{
    if (x < min_x || x > max_x ||
        y < min_y || y > max_y ||
        z < min_z || z > max_z)
            return -1;

    char &cell {grid[x][y][z]};

    if (cell == '#')
        return 1;

    if (cell == '+')
        return 0;

    cell = '+';

    const int sides_x_m {explore(x - 1, y, z)};
    const int sides_x_p {explore(x + 1, y, z)};
    const int sides_y_m {explore(x, y - 1, z)};
    const int sides_y_p {explore(x, y + 1, z)};
    const int sides_z_m {explore(x, y, z - 1)};
    const int sides_z_p {explore(x, y, z + 1)};

    if (sides_x_m < 0 || sides_x_p < 0 ||
        sides_y_m < 0 || sides_y_p < 0 ||
        sides_z_m < 0 || sides_z_p < 0)
            return -1;

    return sides_x_m + sides_x_p + sides_y_m + sides_y_p + sides_z_m + sides_z_p;
}

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    int x, y, z;
    char c;

    unsigned sides {};

    while (in >> x >> c >> y >> c >> z)
    {
        sides += 6;
        grid[x][y][z] = '#';

        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
        if (z < min_z) min_z = z;
        if (z > max_z) max_z = z;

        if (x - 1 >= 0 && grid[x - 1][y][z] == '#')
            sides -= 2;

        if (x + 1 < 50 && grid[x + 1][y][z] == '#')
            sides -= 2;

        if (y - 1 >= 0 && grid[x][y - 1][z] == '#')
            sides -= 2;

        if (y + 1 < 50 && grid[x][y + 1][z] == '#')
            sides -= 2;

        if (z - 1 >= 0 && grid[x][y][z - 1] == '#')
            sides -= 2;

        if (z + 1 < 50 && grid[x][y][z + 1] == '#')
            sides -= 2;
    }

    for (unsigned x {min_x + 1}; x < max_x; ++x)
    {
        for (unsigned y {min_y + 1}; y < max_y; ++y)
        {
            for (unsigned z {min_z + 1}; z < max_z; ++z)
            {
                if (grid[x][y][z] == '.')
                {
                    const int internal_sides {explore(x, y, z)};
                    if (internal_sides > 0)
                        sides -= internal_sides;
                }
            }
        }
    }

    std::cout << sides << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
