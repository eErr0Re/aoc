#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    char opponent, you;
    unsigned score {};

    const unsigned shape_points[][3] {
        {3, 1, 2},
        {1, 2, 3},
        {2, 3, 1}
    };

    const unsigned points[] {0, 3, 6};

    while (in >> opponent >> you)
    {
        score += shape_points[opponent - 'A'][you - 'X'];
        score += points[you - 'X'];
    }

    std::cout << score << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
