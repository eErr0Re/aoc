#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

void find_valid(vector<string> &, string &, int, int);

int main()
{
    auto start = chrono::steady_clock::now();

    vector<string> valid;
    string s(14, '0');
    find_valid(valid, s, 13, 0);

    cout << *max_element(valid.begin(), valid.end()) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";   
}

void find_valid(vector<string> &valid, string &number, int index, int z)
{
    static const int a[] = { 0, 9, 12, 6, 6, 14, 7, 12, 8, 15, 6, 11, 13, 4 };
    static const int b[] = { 0, 0, 0, 0, 15, 23, 0, 0, 17, 24, 0, 20, 22, 13};
    static const bool types[] = { 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1};

    if (index == 13)
    {
        for (int i = b[13]; i > a[13]; --i)
        {
            number[13] = i - a[13] + '0';
            find_valid(valid, number, 12, i);
        }
        return;
    }

    if (!index)
    {
        for (int i = 9; i > 0; --i)
        {
            if (z - i - 1 != 0)
                continue;
            number[0] = i + '0';
            valid.push_back(number);
            return;
        }
    }

    if (!types[index])
    {
        for (int i = 9; i > 0; --i)
        {
            if ((z - i - a[index]) % 26 != 0)
                continue;
            number[index] = i + '0';
            find_valid(valid, number, index - 1, (z - i - a[index]) / 26);
        }
        return;
    }

    for (int i = b[index]; i > a[index]; --i)
    {
        number[index] = i - a[index] + '0';
        find_valid(valid, number, index - 1, z * 26 + i);
    }
}