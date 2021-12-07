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
    int n;
    char c;

    while (in >> n)
    {
        positions.push_back(n);
        in >> c;
    }

    sort(positions.begin(), positions.end());
    int median;

    if (positions.size() % 2)
        median = (positions[positions.size() / 2] + positions[positions.size() / 2 + 1]) / 2;
    else median = (positions[positions.size() / 2]);

    int fuel = 0;

    for (int p : positions)
        fuel += abs(median - p);

    cout << fuel << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n";
}