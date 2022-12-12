#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <array>
#include "Monkey.hpp"

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    std::string line;

    std::vector<Monkey> monkeys;

    Monkey monkey;

    while (in >> monkey)
    {
        monkeys.push_back(std::move(monkey));
        getline(in, line);
    }

    std::vector<unsigned> inspections(monkeys.size(), 0);
 
    for (unsigned round {}; round < 10000; ++round)
    {
        for (unsigned i {}; i < monkeys.size(); ++i)
        {
            auto &monkey {monkeys[i]};
            while (monkey.hasItems())
            {
                ++inspections[i];
                const auto item {monkey.getItem(false)};
                const auto next {monkey.getNextMonkey(item)};
                monkeys[next].addItem(item);
            }
        }
    }

    std::sort(begin(inspections), end(inspections), std::greater<Monkey::WorryLevel>{});

    std::cout << static_cast<unsigned long long>(inspections[0]) * inspections[1] << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
