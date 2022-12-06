#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <queue>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    
    std::string buffer;
    in >> buffer;

    unsigned count {4};

    std::unordered_map<char, unsigned> counts;
    std::queue<char> marker;
    unsigned duplicates {};

    auto addChar = [&counts, &marker, &duplicates](char c)
    {
        marker.push(c);

        if (++counts[c] > 1)
            ++duplicates;
    };

    for (unsigned i {}; i < 4; ++i)
    {
        addChar(buffer[i]);
    }

    for (unsigned i {4}; duplicates && i < buffer.size(); ++i)
    {
        char removed {marker.front()};
        marker.pop();

        if (--counts[removed] > 0)
            --duplicates;

        addChar(buffer[i]);

        ++count;
    }

    std::cout << count << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
