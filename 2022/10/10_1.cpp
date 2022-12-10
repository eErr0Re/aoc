#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

char pixelColour(unsigned pixel_cycle, int x)
{
    const unsigned position {(pixel_cycle - 1) % 40};
    if (abs(x - static_cast<int>(position)) <= 1)
        return '#';
    return '.';
}

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
  
    unsigned cycle {1};
    unsigned pixel_cycle {1};
    const unsigned last_pixel {240};

    int X {1};

    std::string instruction;
    int val;

    while (pixel_cycle <= last_pixel && in >> instruction)
    {
        const auto prev_X {X};

        if (instruction == "addx")
        {
            in >> val;
            X += val;
            cycle += 2;
        }
        else ++cycle;

        while (pixel_cycle <= last_pixel && pixel_cycle <= cycle)
        {
            std::cout << pixelColour(pixel_cycle, pixel_cycle == cycle ? X : prev_X);
            if (pixel_cycle % 40 == 0)
                std::cout << '\n';
            ++pixel_cycle;
        }
    }

    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
