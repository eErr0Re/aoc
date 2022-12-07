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

    Node root {"/"};
    Node *current_node {&root};

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

    root.calculateSize();

    std::stack<const Node *> to_visit;
    to_visit.push(&root);

    const Node::size_type target_size {100000};

    Node::size_type total_size {};

    while (!to_visit.empty())
    {
        const Node *current {to_visit.top()};
        to_visit.pop();

        const Node::size_type size {current->getSize()};
        if (size <= target_size)
            total_size += size;

        for (const auto &dir : current->getDirectories())
            to_visit.push(&dir.second);
    }
 
    std::cout << total_size << '\n';
    const auto end {std::chrono::steady_clock::now()};
    std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
}
