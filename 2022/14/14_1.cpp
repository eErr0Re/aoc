#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    std::string line;

    const unsigned width {1000};
    const unsigned height {300};

    std::vector<std::vector<char>> cave(height, std::vector<char>(width, '.'));

    int x, y;
    char c;

    unsigned max_y {};

    while (getline(in, line))
    {
        std::stringstream ss {line};

        int prev_x {width};
        int prev_y {height};

        while (ss >> x >> c >> y)
        {
            if (prev_x == width)
                cave[y][x] = '#';
            else if (x == prev_x)
            {
                int add {y - prev_y > 0 ? 1 : -1};
                for (int new_y {prev_y + add}; new_y != y + add; new_y += add)
                    cave[new_y][x] = '#';
            }
            else
            {
                int add {x - prev_x > 0 ? 1 : -1};
                for (int new_x {prev_x + add}; new_x != x + add; new_x += add)
                    cave[y][new_x] = '#';
            }

            prev_x = x;
            prev_y = y;

            if (y > max_y)
                max_y = y;

            ss >> c >> c;
        }
    }

    ++max_y;

    unsigned count {};

    for (bool stop {false}; !stop;)
    {
        unsigned cur_x {500};
        unsigned cur_y {0};

        for (bool moved {true}; moved;)
        {
            if (cur_y == max_y)
                break;

            if (cave[cur_y + 1][cur_x] == '.')
                ++cur_y;
            else if (cave[cur_y + 1][cur_x - 1] == '.')
            {
                ++cur_y;
                --cur_x;
            }
            else if (cave[cur_y + 1][cur_x + 1] == '.')
            {
                ++cur_y;
                ++cur_x;
            }
            else moved = false;
        }

        cave[cur_y][cur_x] = 'o';

        if (cur_x == 500 && cur_y == 0)
            stop = true;

        ++count;
    }

    std::cout << count << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
