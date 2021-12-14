#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    unordered_map<string, char> rules;
    string polymer;
    in >> polymer;
    string a, b;
    char c;

    while (in >> a >> b >> c)
        rules.insert({a, c});

    for (int i = 0; i < 10; ++i)
    {
        string temp(1, polymer[0]);
        for (int j = 1; j < polymer.size(); ++j)
        {
            temp += rules[polymer.substr(j - 1, 2)];
            temp += polymer[j];
        }
        polymer = temp;
    }

    unordered_map<char, int> quantity;

    for (char c : polymer)
        ++quantity[c];

    int min = INT_MAX, max = -1;

    for (pair<char, int> p : quantity)
    {
        if (p.second < min) min = p.second;
        if (p.second > max) max = p.second;
    }

    cout << max - min << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}