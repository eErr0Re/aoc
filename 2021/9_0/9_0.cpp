#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string line;
    vector<vector<int>> field;
    int sum = 0;

    while (in >> line)
    {
        vector<int> row;
        for (char c : line)
            row.push_back(c - '0');
        field.push_back(row);
    }

    for (int i = 0; i < field.size(); ++i)
    {
        for (int k = 0; k < field[0].size(); ++k)
        {
            if (k - 1 >= 0 && field[i][k] >= field[i][k - 1])
                continue;
            if (k + 1 < field[0].size() && field[i][k] >= field[i][k + 1])
                continue;
            if (i - 1 >= 0 && field[i][k] >= field[i - 1][k])
                continue;
            if (i + 1 < field.size() && field[i][k] >= field[i + 1][k])
                continue;
            sum += field[i][k++] + 1;
        }
    }

    cout << sum << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}