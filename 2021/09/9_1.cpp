#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

int calculate_basin(vector<vector<int>> &, int, int);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string line;
    vector<vector<int>> field;
    vector<int> basins;
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
            basins.push_back(calculate_basin(field, i, k));
        }
    }

    sort(basins.rbegin(), basins.rend());

    cout << basins[0] * basins[1] * basins[2] << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

int calculate_basin(vector<vector<int>> &field, int i, int k)
{
    int val = field[i][k];
    if (val == -1 || val == 9)
        return 0;
    field[i][k] = -1;
    int sum = 1;
    if (k - 1 >= 0 && val < field[i][k - 1])
        sum += calculate_basin(field, i, k - 1);
    if (k + 1 < field[0].size() && val < field[i][k + 1])
        sum += calculate_basin(field, i, k + 1);
    if (i - 1 >= 0 && val < field[i - 1][k] && field[i - 1][k])
        sum += calculate_basin(field, i - 1, k);
    if (i + 1 < field.size() && val < field[i + 1][k] && field[i + 1][k])
        sum += calculate_basin(field, i + 1, k);
    return sum;
}