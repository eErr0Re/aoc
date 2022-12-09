#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <string>

class Directory;

class Node
{
public:
    using size_type = unsigned;

    Node() :
        Node("") {}

    explicit Node(std::string_view name, size_type size = 0, Directory *parent = nullptr) :
        m_name {name}, m_size {size}, m_parent {parent} {}

    size_type getSize() const noexcept
    {
        return m_size;
    }

protected:
    std::string m_name;
    size_type m_size;
    Directory *m_parent;
};

class Directory : public Node
{
public:
    using Node::Node;

    Directory *getDirectory(std::string_view name)
    {
        if (name == "..")
            return m_parent;

        if (m_directories.contains(name.data()))
            return &m_directories[name.data()];

        return nullptr;
    }

    const std::unordered_map<std::string, Directory> &getDirectories() const noexcept
    {
        return m_directories;
    }

    size_type calculateSize()
    {
        size_type size {};

        for (auto &file : m_files)
            size += file.second.getSize();

        for (auto &dir : m_directories)
            size += dir.second.calculateSize();

        m_size = size;
        return size;
    }

    void addDirectory(std::string_view name)
    {
        m_directories.try_emplace(name.data(), name, 0, this);
    }

    void addFile(std::string_view name, size_type size)
    {
        m_files.try_emplace(name.data(), name, size, this);
    }

private:
    std::unordered_map<std::string, Node> m_files;
    std::unordered_map<std::string, Directory> m_directories;
};

#endif
