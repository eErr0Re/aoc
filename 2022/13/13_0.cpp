#include <iostream>
#include <fstream>
#include <chrono>
#include "List.hpp"

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    std::string line;
    
    List packet1, packet2;

    unsigned sum {};
    unsigned index {1};

    while (in >> packet1 >> packet2)
    {
        if (packet1 < packet2)
            sum += index;

        ++index;
    }
    
    std::cout << sum << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
