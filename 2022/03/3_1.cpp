#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    std::string sack;
    unsigned sum {};

    while (in >> sack)
    {
        std::unordered_map<char, unsigned> counts;
        char badge;

        for (unsigned i {}; i < 3; ++i)
        {
            const std::unordered_set<char> items(sack.cbegin(), sack.cend());
            
            for (const char item : items)
            {
                ++counts[item];
                if (i == 2 && counts[item] == 3)
                {
                    badge = item;
                    break;
                }
            }
            
            if (i < 2)
                in >> sack;
        }

        const char offset = islower(badge) ? 'a' - 1 : 'A' - 27;
        sum += badge - offset;
    }

    std::cout << sum << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
