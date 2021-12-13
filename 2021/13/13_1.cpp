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
    int x, y;
    char c;
    vector<vector<bool>> paper;
    int max_x = 0;

    // Read coordinates
    while (in >> x >> c >> y)
    {
        for (int i = paper.size() - 1; i < y; ++i)
            paper.push_back(vector<bool>());

        for (int i = paper[y].size() - 1; i < x; ++i)
            paper[y].push_back(0);

        paper[y][x] = 1;

        if (x > max_x) max_x = x;
    }

    in.clear();

    string a;
    char dir;
    int val;

    int y_size = paper.size();
    int x_size = max_x + 1;

    // Fold
    while (in >> a >> a >> dir >> c >> val)
    {
        // Fold up
        if (dir == 'y')
        {
            int new_size = max(y_size - val - 1, val); // New y_size
            vector<vector<bool>> temp(new_size, vector<bool>(x_size, 0)); // New paper with the new y_size

            // Bottom half is larger
            if (val < y_size / 2)
            {
                // Add rows from the bottom half in increasing order of the new paper and decreasing order of the old paper (last row of the old paper to row 0 of the new paper)
                for (int i = 0, k = y_size - 1; k > val; --k, ++i)
                    for (int j = 0; j < paper[k].size(); ++j)
                        temp[i][j] = paper[k][j];

                // Add rows from the upper half in increasing order of the new and old paper (first row of the old paper to the appropriate row of the new paper)
                for (int i = new_size - val, k = 0; k < val; ++i, ++k)
                    for (int j = 0; j < paper[k].size(); ++j)
                        temp[i][j] = temp[i][j] | paper[k][j];
            }
            // Bottom half is smaller/equal
            else
            {
                // Add rows from the upper half in increasing order of the new and old paper (first row of the old paper to the first row of the new paper)
                for (int i = 0, k = 0; k < val; ++k, ++i)
                    for (int j = 0; j < paper[k].size(); ++j)
                        temp[i][j] = paper[k][j];

                // Add rows from the bottom half in decreasing order of the new paper and increasing order of the old paper (first row of the old paper after the fold to the last row of the new paper)
                for (int i = new_size - 1, k = val + 1; k < y_size; --i, ++k)
                    for (int j = 0; j < paper[k].size(); ++j)
                        temp[i][j] = temp[i][j] | paper[k][j];
            }

            y_size = new_size;
            paper = temp;
        }

        // Fold left
        if (dir == 'x')
        {
            int new_size = max(x_size - val - 1, val); // New x_size
            vector<vector<bool>> temp(y_size, vector<bool>(new_size, 0)); // New paper with the new x_size

            // Right side is larger
            if (val < x_size / 2)
            {
                // Iterate over each row
                for (int i = 0; i < y_size; ++i)
                    // Add values from the right side in increasing order of the new paper and decreasing order of the old paper (last value of the old paper to the first value of the new paper)
                    for (int j = 0, k = x_size - 1; k > val; --k, ++j)
                    {
                        if (k >= paper[i].size())
                            continue;
                        temp[i][j] = paper[i][k];
                    }

                // Iterate over each row
                for (int i = 0; i < y_size; ++i)
                    // Add values from the right side in increasing order of the new and old paper (first value of the left side to the appropriate value of the right side)
                    for (int j = new_size - val, k = 0; k < paper[i].size(); ++j, ++k)
                        temp[i][j] = temp[i][j] | paper[i][k];
            }
            // Right side is smaller/equal
            else
            {
                // Iterate over each row
                for (int i = 0; i < y_size; ++i)
                    // Add values from the left side in increasing order of the new and old paper (first value to first value)
                    for (int j = 0; j < val && j < paper[i].size(); ++j)
                        temp[i][j] = paper[i][j];

                // Iterate over each row
                for (int i = 0; i < y_size; ++i)
                    // Add values from the right side in decreasing order of the new paper and increasing order of the old paper (first value of the old paper after the fold to the last value of the new paper)
                    for (int j = new_size - 1, k = val + 1; k < paper[i].size(); --j, ++k)
                        temp[i][j] = temp[i][j] | paper[i][k];
            }

            x_size = new_size;
            paper = temp;
        }
    }

    // Print the result
    for (int i = 0; i < y_size; ++i)
    {
        for (int j = 0; j < x_size && j < paper[i].size(); ++j)
            cout << (paper[i][j] ? "\u2588" : "\u2591");
        cout << '\n';
    }
    
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}