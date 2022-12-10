#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
  
    unsigned cycle {1};
    unsigned target_cycle {20};
    const unsigned max_cycle {220};
    const unsigned step {40};

    int X {1};

    std::string instruction;
    int val;

    unsigned signal_strength {};

    while (cycle < max_cycle && in >> instruction)
    {
        const auto prev_X {X};
        
        if (instruction == "addx")
        {
            in >> val;
            X += val;
            cycle += 2;
        }
        else ++cycle;

        if (cycle >= target_cycle)
        {
            if (cycle == target_cycle)
                signal_strength += X * target_cycle;
            else signal_strength += prev_X * target_cycle;

            target_cycle += step; 
        }
    }

    std::cout << signal_strength << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
