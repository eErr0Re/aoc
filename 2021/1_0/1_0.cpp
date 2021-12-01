#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream in = ifstream("input.txt");
    int prev, current;
    in >> prev;
    int count = 0;
    while (in >> current)
    {
        if (current > prev)
            ++count;
        prev = current;
    }
    cout << count << '\n';
}