#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string polymer;
    in >> polymer;
    string a, b;
    char c;

    unordered_map<string, char> rules;
    unordered_map<string, unsigned long long> pairs;
    unordered_map<char, unsigned long long> count;

    ++count[polymer[0]];
    for (int i = 1; i < polymer.size(); ++i)
    {
        ++pairs[string(1, polymer[i - 1]) + polymer[i]];
        ++count[polymer[i]];
    }

    while (in >> a >> b >> c)
        rules.insert({a, c});

    for (int i = 0; i < 40; ++i)
    {
        unordered_map<string, unsigned long long> new_pairs = pairs;
        for (pair<string, unsigned long long> p : pairs)
        {
            count[rules[p.first]] += p.second;
            new_pairs[p.first] -= p.second;
            new_pairs[string(1, p.first[0]) + rules[p.first]] += p.second;
            new_pairs[string(1, rules[p.first]) + p.first[1]] += p.second;
        }
        pairs = new_pairs;
    }

    unsigned long long min = ULLONG_MAX, max = 0;

    for (pair<char, unsigned long long> p : count)
    {
        if (p.second < min) min = p.second;
        if (p.second > max) max = p.second;
    }

    cout << max - min << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}