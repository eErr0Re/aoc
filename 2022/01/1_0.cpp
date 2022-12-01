#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    std::string line;
    unsigned sum {};
    unsigned max {};

    while (std::getline(in, line))
    {
        if (line.empty())
        {
            if (sum > max)
                max = sum;
            sum = 0;
            continue;
        }

        sum += stoi(line);
    }

    std::cout << max << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
