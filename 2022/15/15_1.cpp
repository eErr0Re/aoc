#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>


struct Interval
{
    int x1;
    int x2;
};

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    std::string word;
    int sensor_x, sensor_y;
    int beacon_x, beacon_y;
    char c;

    const int max {4000000};

    std::vector<std::vector<Interval>> intervals(max + 1, std::vector<Interval>());

    while (in >> word >> word >> c >> c >> sensor_x >> c >> c >> c >> sensor_y >> c >> word >> word >> word >> word >> c >> c >> beacon_x >> c >> c >> c >> beacon_y)
    {
        const int dist {abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y)};

        for (int row {std::max(0, sensor_y - dist)}; row <= std::min(max, sensor_y + dist); ++row)
        {
            const int dist_from_row {sensor_y > row ? row - sensor_y + dist : sensor_y + dist - row};

            intervals[row].emplace_back(sensor_x - dist_from_row, sensor_x + dist_from_row + 1);
        }
    }

    for (unsigned i {}; i <= max; ++i) 
    {
        auto &row {intervals[i]};

        std::sort(begin(row), end(row), [](const Interval &i1, const Interval &i2) {
            return i1.x1 < i2.x1;
        });

        int done {row[0].x1};

        if (done > 0)
        {
            std::cout << 0 << '\n';
            break;
        }

        bool found {false};
        for (const auto &interval : row)
        {
            if (interval.x1 - done > 0)
            {
                found = true;
                break;
            }
            done = std::max(interval.x2, done);
        }

        if (done == max || found)
        {
            std::cout << static_cast<unsigned long long>(done) * max + i << '\n';
            break;
        }
    }

    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
