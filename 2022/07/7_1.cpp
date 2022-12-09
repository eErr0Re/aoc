#include <iostream>
#include <fstream>
#include <chrono>
#include <stack>
#include "Node.hpp"

int main()
{
    const auto start {std::chrono::steady_clock::now()};

    std::ifstream in {"input.txt"};
    std::string word;

    Directory root {"/"};
    Directory *current_node {&root};

    getline(in, word);
    while (in >> word)
    {
        if (word == "$")
        {
            in >> word;

            if (word == "ls")
                continue;

            in >> word;

            current_node = current_node->getDirectory(word);
        }
        else
        {
            if (word == "dir")
            {
                in >> word;
                current_node->addDirectory(word);
            }
            else
            {
                const Node::size_type size {static_cast<Node::size_type>(stoul(word))};
                in >> word;
                current_node->addFile(word, size);
            }
        }
    }

    const Node::size_type total_space {70000000};
    const Node::size_type required_space {30000000};

    const Node::size_type unused_space {total_space - root.calculateSize()};
    const Node::size_type target_size {required_space - unused_space};

    Node::size_type smallest {total_space};

    std::stack<const Directory *> to_visit;
    to_visit.push(&root);

    while (!to_visit.empty())
    {
        const Directory *current {to_visit.top()};
        to_visit.pop();

        const Node::size_type size {current->getSize()};
        if (size >= target_size && size < smallest)
            smallest = size;

        for (const auto &dir : current->getDirectories())
            to_visit.push(&dir.second);
    }
 
    std::cout << smallest << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
