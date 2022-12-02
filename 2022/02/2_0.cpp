#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    char opponent, you;
    unsigned score {};

    const unsigned points[][3] {
        {3, 6, 0},
        {0, 3, 6},
        {6, 0, 3}
    };

    const unsigned shape_points[] {1, 2, 3};

    while (in >> opponent >> you)
    {
        score += shape_points[you - 'X'];
        score += points[opponent - 'A'][you - 'X'];
    }

    std::cout << score << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
