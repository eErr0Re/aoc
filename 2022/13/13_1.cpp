#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "List.hpp"

List createDivider(unsigned val)
{
    List divider;
    List divider_nested {&divider};
    divider_nested.add(List {val, &divider_nested});
    divider.add(std::move(divider_nested));

    return divider;
}

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    std::string line;

    List packet;

    std::vector<List> packets;

    List divider1 {createDivider(2)};
    packets.push_back(divider1);

    List divider2 {createDivider(6)};
    packets.push_back(divider2);
    
    while (in >> packet)
        packets.push_back(std::move(packet));
    
    std::sort(begin(packets), end(packets));

    unsigned key {1};
    for (size_t i {}; i < packets.size(); ++i)
    {
        if (packets[i] == divider1 || packets[i] == divider2)
            key *= i + 1;
    }

    std::cout << key << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
