#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <string>

class Node
{
public:
    using size_type = unsigned;

    Node() :
        Node("") {}

    explicit Node(std::string_view name, size_type size = 0, bool file = false, Node *parent = nullptr) :
        m_name {name}, m_size {size}, m_file {file}, m_parent {parent} {}

    size_type getSize() const noexcept
    {
        return m_size;
    }

    Node *getDirectory(std::string_view name)
    {
        if (name == "..")
            return m_parent;

        return &(m_directories[name.data()]);
    }

    const std::unordered_map<std::string, Node> &getDirectories() const noexcept
    {
        return m_directories;
    }

    size_type calculateSize()
    {
        if (m_file)
            return m_size;

        size_type size {};

        for (auto &file : m_files)
            size += file.second.calculateSize();

        for (auto &dir : m_directories)
            size += dir.second.calculateSize();

        m_size = size;
        return size;
    }

    void addDirectory(std::string_view name)
    {
        m_directories.try_emplace(name.data(), name, 0, false, this);
    }

    void addFile(std::string_view name, size_type size)
    {
        m_files.try_emplace(name.data(), name, size, true, this);
    }

private:
    std::string m_name;
    size_type m_size;
    bool m_file;
    std::unordered_map<std::string, Node> m_files;
    std::unordered_map<std::string, Node> m_directories;
    Node *m_parent;
};

#endif
