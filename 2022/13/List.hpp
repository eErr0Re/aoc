#ifndef LIST_H
#define LIST_H

#include <vector>
#include <memory>
#include <compare>

class List
{
public:
    friend std::istream &operator>>(std::istream &in, List &list);
    friend std::ostream &operator<<(std::ostream &out, const List &list);

    explicit List(List *parent = nullptr) :
        m_parent {parent},
        m_is_value {false}
    {};

    explicit List(unsigned value, List *parent = nullptr) :
        m_parent {parent},
        m_value {value},
        m_is_value {true}
    {}

    void add(List element)
    {
        m_elements.push_back(std::move(element));
    }

    std::strong_ordering operator<=>(const List &other) const
    {
        if (m_is_value && other.m_is_value)
            return m_value <=> other.m_value;
        
        List new_list1;
        List new_list2;

        const List *list1 = this;
        if (m_is_value)
        {
            new_list1.m_elements.push_back(*this);
            list1 = &new_list1;
        }

        const List *list2 = &other;
        if (other.m_is_value)
        {
            new_list2.m_elements.push_back(other);
            list2 = &new_list2;
        }

        const size_t min_size {std::min(list1->m_elements.size(), list2->m_elements.size())};

        for (size_t i {}; i < min_size; ++i)
        {
            const auto comp {list1->m_elements[i] <=> list2->m_elements[i]};

            if (comp == std::strong_ordering::less || comp == std::strong_ordering::greater)
                return comp;
        }

        return list1->m_elements.size() <=> list2->m_elements.size();
    }

    bool operator==(const List &other)
    {
        return *this <=> other == std::strong_ordering::equal;
    }

private:
    List *m_parent;
    std::vector<List> m_elements;
    unsigned m_value;
    bool m_is_value;
};

std::istream &operator>>(std::istream &in, List &list)
{
    list = List();
    List *current = &list;

    char c;
    unsigned val;

    if (!(in >> c) || c != '[')
        return in;

    while (current != nullptr)
    {
        if (in >> val)
            current->m_elements.emplace_back(val, current);
        else in.clear();

        if (in >> c)
        {
            switch (c)
            {
                case '[':
                    current->m_elements.emplace_back(current);
                    current = &current->m_elements.back();
                    break;
                case ']':
                    current = current->m_parent;
                    break;
                case ',':
                    break;
                default:
                    in.setstate(std::ios_base::failbit);
                    break;
            }
        }
        else in.clear();
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const List &list)
{
    if (list.m_is_value)
    {
        out << list.m_value;
        return out;
    }

    out << '[';
    for (size_t i {}; i < list.m_elements.size(); ++i)
    {
        out << list.m_elements[i];
        if (i < list.m_elements.size() - 1)
            out << ',';
    }
    out << ']';
    return out;
}

#endif
