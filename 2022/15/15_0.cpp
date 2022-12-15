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

    std::string str;
    int sensor_x, sensor_y;
    int beacon_x, beacon_y;
    char c;

    const int row {2000000};

    std::vector<Interval> intervals;

    while (in >> str >> str >> c >> c >> sensor_x >> c >> c >> c >> sensor_y >> c >> str >> str >> str >> str >> c >> c >> beacon_x >> c >> c >> c >> beacon_y)
    {
        const int dist {abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y)};
        if (sensor_y - dist >= row || sensor_y + dist <= row)
            continue;

        const int dist_from_row {sensor_y > row ? row - sensor_y + dist : sensor_y + dist - row};

        Interval interval {sensor_x - dist_from_row, sensor_x + dist_from_row + 1};
        if (beacon_y == row)
        {
            if (beacon_x < sensor_x)
                ++interval.x1;
            else --interval.x2;
        }

        intervals.push_back(interval);
    }

    std::sort(begin(intervals), end(intervals), [](const Interval &i1, const Interval &i2) {
        return i1.x1 < i2.x1;
    });

    int done {intervals[0].x1};
    unsigned positions {};

    for (const auto &i : intervals)
    {
        positions += std::max(i.x2, done) - std::max(i.x1, done);
        done = std::max(i.x2, done);
    }

    std::cout << positions << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
