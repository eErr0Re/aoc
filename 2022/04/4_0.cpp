#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    unsigned a0, a1, b0, b1;
    char c;

    unsigned overlaps {};

    while (in >> a0 >> c >> a1 >> c >> b0 >> c >> b1)
    {
        if (a0 >= b0 && a1 <= b1 || b0 >= a0 && b1 <= a1)
            ++overlaps;
    }

    std::cout << overlaps << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
