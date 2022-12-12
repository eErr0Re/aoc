#ifndef MONKEY_H
#define MONKEY_H

#include <queue>
#include <functional>

class Monkey
{
public:
    using WorryLevel = unsigned long long;
    using Function = std::function<WorryLevel(WorryLevel, WorryLevel)>;

    friend std::istream &operator>>(std::istream& in, Monkey &monkey);
    friend std::ostream &operator<<(std::ostream& out, const Monkey &monkey);

    Monkey() :
        m_test_divide {},
        m_throw_true {},
        m_throw_false {},
        m_operation_val {}
    {}

    Monkey(std::queue<WorryLevel> items, unsigned test_divide, unsigned throw_true, unsigned throw_false,
        const Function &operation, unsigned operation_val) :

        m_items {std::move(items)},
        m_test_divide {test_divide},
        m_throw_true {throw_true},
        m_throw_false {throw_false},
        m_operation {operation},
        m_operation_val {operation_val}
    {
        s_product *= test_divide;
    }
    
    bool hasItems() const
    {
        return !m_items.empty();
    }


    void addItem(WorryLevel item)
    {
        m_items.push(item);
    }
    
    WorryLevel getItem(bool divide_worry_level)
    {
        WorryLevel item {m_items.front()};
        m_items.pop();

        item = m_operation(item, m_operation_val);

        if (divide_worry_level)
            item /= 3;
        else item %= s_product;

        return item;
    }

    unsigned getNextMonkey(WorryLevel item) const
    {
        if (item % m_test_divide)
            return m_throw_false;
        return m_throw_true;
    }

private:
    std::queue<WorryLevel> m_items;
    unsigned m_test_divide;
    unsigned m_throw_true;
    unsigned m_throw_false;
    Function m_operation;
    unsigned m_operation_val;

    inline static WorryLevel s_product {1};
};

Monkey::WorryLevel mulOld(Monkey::WorryLevel old, Monkey::WorryLevel val)
{
    return old * old;
}

std::istream &operator>>(std::istream& in, Monkey &monkey)
{
    std::string line;
    std::string word;

    if (!getline(in, line))
        return in;

    monkey.m_items = {};

    // Items
    getline(in, line);
    std::stringstream ss {line};
    ss >> word >> word;

    while (ss >> word)
        monkey.m_items.push(stoi(word));

    // Operation
    getline(in, line);
    ss.clear();
    ss.str(line);
    char op;
    ss >> word >> word >> word >> word >> op >> word;

    if (op == '+')
    {
        monkey.m_operation_val = stoi(word);
        monkey.m_operation = std::plus<Monkey::WorryLevel> {};
    }
    else
    {
        if (word == "old")
            monkey.m_operation = mulOld;
        else
        {
            monkey.m_operation_val = stoi(word);
            monkey.m_operation = std::multiplies<Monkey::WorryLevel> {};
        }
    }

    // Test
    getline(in, line);
    ss.clear();
    ss.str(line);
    ss >> word >> word >> word >> monkey.m_test_divide;

    monkey.s_product *= monkey.m_test_divide;

    // True
    getline(in, line);
    ss.clear();
    ss.str(line);
    ss >> word >> word >> word >> word >> word >> monkey.m_throw_true;

    // False
    getline(in, line);
    ss.clear();
    ss.str(line);
    ss >> word >> word >> word >> word >> word >> monkey.m_throw_false;

    return in;
}

std::ostream &operator<<(std::ostream& out, const Monkey &monkey)
{
    out << "Starting items: ";
    auto items {monkey.m_items};\
    while (!items.empty())
    {
        out << items.front() << ' ';
        items.pop();
    }

    out << "\nOperation val: " << monkey.m_operation_val;

    out << "\nTest val: " << monkey.m_test_divide;

    out << "\nTrue val: " << monkey.m_throw_true;

    out << "\nFalse val: " << monkey.m_throw_false << '\n';

    return out;
}

#endif
