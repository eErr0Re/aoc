#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int flash (int[10][10], int, int);
void evaluate(int[10][10], vector<pair<int, int>> &, int, int);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    int field[10][10];
    char c;

    // Read input
    for (int k = 0; k < 10; ++k)
    {
        for (int i = 0; i < 10; ++i)
        {
            in >> c;
            field[k][i] = c - '0';
        }
        
    }

    int result = 0;

    // 100 steps
    for (int i = 0; i < 100; ++i)
    {
        // Increment all values
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                ++field[j][k];

        // Flash positions with value > 9
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                if (field[j][k] > 9)
                    result += flash(field, j, k);

        // Set all flashed positions to 0
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                if (field[j][k]  == -1)
                    field[j][k] = 0;
    }

    cout << result << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

// Flash position
int flash(int field[10][10], int j, int k)
{
    int result = 1;
    field[j][k] = -1;
    vector<pair<int, int>> flashes;

    // Evaluate all adjecent positions
    for (int a = -1; a < 2; ++a)
    {
        for (int b = -1; b < 2; ++b)
        {
            if (a == 0 && b == 0)
                continue;
            evaluate(field, flashes, j + a, k + b);
        }
    }

    // Flash all positions with value > 9
    for (pair<int, int> pos : flashes)
        result += flash(field, pos.first, pos.second);

    return result;
}

// Evaluate the position
void evaluate(int field[10][10], vector<pair<int, int>> &flashes, int j, int k)
{
    if (j >= 0 && j < 10 && k >= 0 && k < 10 && field[j][k] != -1)
    {
        if (field[j][k] == 9)
            flashes.push_back({j, k});
        ++field[j][k];
    }
}