#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    std::string line;
    unsigned sum {};
    unsigned max[] {0, 0, 0};

    while (std::getline(in, line))
    {
        if (line.empty())
        {
            std::sort(std::begin(max), std::end(max));
            if (sum > max[0])
                max[0] = sum;
            sum = 0;
            continue;
        }

        sum += stoi(line);
    }

    unsigned total {max[0] + max[1] + max[2]};

    std::cout << total << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
