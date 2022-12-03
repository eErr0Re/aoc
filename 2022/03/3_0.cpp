#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    std::string sack;
    unsigned sum {};

    while (in >> sack)
    {
        std::unordered_set<char> first_compartment(sack.cbegin(), sack.cbegin() + sack.size() / 2);

        for (auto it {sack.cbegin() + sack.size() / 2}; it != sack.cend(); ++it)
        {
            if (first_compartment.contains(*it))
            {
                const char offset = islower(*it) ? 'a' - 1 : 'A' - 27;
                sum += *it - offset;
                break;
            }
        }
    }

    std::cout << sum << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
