#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <unordered_set>
#include <queue>
#include <functional>
#include <array>

struct Point
{
    int x {};
    int y {};

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

Point left(const Point &point)
{
    return {point.x - 1, point.y};
}

Point right(const Point &point)
{
    return {point.x + 1, point.y};
}

Point up(const Point &point)
{
    return {point.x, point.y + 1};
}

Point down(const Point &point)
{
    return {point.x, point.y - 1};
}

struct PointHash
{
    std::size_t operator () (const Point &point) const
    {
        return std::hash<int>{}(point.x) * std::hash<int>{}(point.y);
    }
};

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    std::string row;

    std::vector<std::string> grid;
    std::unordered_set<Point, PointHash> visited;
    std::queue<Point> to_visit;

    Point finish;

    for (unsigned y {}; in >> row; ++y)
    {
        if (to_visit.empty())
        {
            const auto x {row.find('S')};
            if (x != std::string::npos)
            {
                row[x] = 'a';
                to_visit.emplace(x, y);
                visited.emplace(x, y);
            }
        }

        const auto x {row.find('E')};
        if (x != std::string::npos)
        {
            row[x] = 'z';
            finish = {static_cast<int>(x), static_cast<int>(y)};
        }

        grid.push_back(row);
    }

    unsigned steps {};

    std::array<std::function<Point(const Point &)>, 4> moves {left, right, up, down};

    bool found {false};
    while (!found && !to_visit.empty())
    {
        ++steps;
        std::queue<Point> current_level;
        current_level.swap(to_visit);
        
        while (!current_level.empty())
        {
            const auto &cur {current_level.front()};
            current_level.pop();

            const char c {grid[cur.y][cur.x]};
            
            if (cur == finish)
            {
                found = true;
                break;
            }

            for (const auto &move : moves)
            {
                Point next {move(cur)};

                if (next.x < 0 || next.x >= grid[0].size()
                    || next.y < 0 || next.y >= grid.size())
                    continue;

                if (grid[next.y][next.x] - c > 1)
                    continue;

                if (visited.contains(next))
                    continue;

                visited.insert(next);
                to_visit.push(std::move(next));
            }
        }
    }

    --steps;

    std::cout << steps << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
