#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    vector<int> positions;
    int n, avg;
    char c;

    while (in >> n)
    {
        positions.push_back(n);
        avg += n;
        in >> c;
    }

    avg /= positions.size();

    int fuel = 0;
    for (int p : positions)
    {
        int steps = abs(p - avg);
        fuel += steps * (steps + 1) / 2;
    }


    cout << fuel << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n";
}