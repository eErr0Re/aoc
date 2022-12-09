#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

struct Point
{
    int x {};
    int y {};

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

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
    char direction;
    unsigned steps;

    Point knots[10];
    std::unordered_set<Point, PointHash> visited;
    visited.insert(knots[9]);

    Point &head {knots[0]};
    const Point &tail {knots[9]};

    while (in >> direction >> steps)
    {
        for (unsigned i {}; i < steps; ++i)
        {
            switch (direction)
            {
                case 'L':
                    --head.x;
                    break;
                case 'R':
                    ++head.x;
                    break;
                case 'D':
                    --head.y;
                    break;
                case 'U':
                    ++head.y;
                    break;
            }

            for (unsigned j {1}; j < 10; ++j)
            {
                Point &cur {knots[j]};
                const Point &prev {knots[j - 1]};

                int difference_x {prev.x - cur.x};
                int difference_y {prev.y - cur.y};

                if (prev.x != cur.x && prev.y != cur.y  && (abs(difference_x) > 1 || abs(difference_y) > 1))
                {
                    cur.x += difference_x < 0 ? -1 : 1;
                    cur.y += difference_y < 0 ? -1 : 1;
                }
                else if (abs(difference_x) > 1)
                {
                    difference_x += difference_x < 0 ? 1 : -1;
                    cur.x += difference_x;
                }
                else if (abs(difference_y) > 1)
                {
                    difference_y += difference_y < 0 ? 1 : -1;
                    cur.y += difference_y;
                }
            }
            
            visited.insert(tail);
        }
    }

    std::cout << visited.size() << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
