#include <iostream>
#include <fstream>
#include <chrono>
#include <deque>

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};

    std::string line;
    std::getline(in, line);

    const size_t n_stacks {(line.size() + 1) / 4};
    std::deque<char> stacks[n_stacks];

    do
    {
        for (unsigned i {}; i < n_stacks; ++i)
        {
            char c {line[i * 4 + 1]};
            if (c != ' ')
                stacks[i].push_back(c);
        }
    } while (std::getline(in, line) && line[1] != '1');

    std::getline(in, line);

    unsigned n, src, dest;
    std::string str;

    while (in >> str >> n >> str >> src >> str >> dest)
    {
        for (unsigned i {}; i < n; ++i)
        {
            stacks[dest - 1].push_front(stacks[src - 1].front());
            stacks[src - 1].pop_front();
        }
    }

    std::string answer;
    answer.reserve(n_stacks);

    for (const auto &stack : stacks)
        answer += stack.front();

    std::cout << answer << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
