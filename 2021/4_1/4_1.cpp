#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

bool solve(vector<vector<vector<int>>> &, int);
bool check(vector<vector<vector<int>>> &);
int score(vector<vector<vector<int>>> const &, int);

int main()
{
    ifstream in("input.txt");
    string line;
    vector<int> values;
    vector<vector<vector<int>>> fields;

    in >> line;
    stringstream ss(line);
    int val;
    char c;
    while (ss >> val)
    {
        values.push_back(val);
        ss >> c;
    }

    while (!in.eof())
    {
        vector<vector<int>> field(5, vector<int>(5));
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                in >> field[i][j];

        fields.push_back(field);
    }

    bool win = false;
    int last;
    for (int i = 0; i < values.size(); ++i)
    {
        int sz = fields.size();
        win = solve(fields, values[i]);
        last = values[i];
        if (sz == 1 && win)
            break;
        else win = false;
    }

    cout << score(fields, last) << endl;
}

bool solve(vector<vector<vector<int>>> &fields, int val)
{
    for (int i = 0; i < fields.size(); ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            bool found = false;
            for (int k = 0; k < 5; ++k)
            {
                if (fields[i][j][k] == val)
                {
                    fields[i][j][k] = -1;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }
    return check(fields);

}

bool check(vector<vector<vector<int>>> &fields)
{
    bool win = false;
    for (int i = 0; i < fields.size(); ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            bool winner_horizontal = true;
            bool winner_vertical = true;
            for (int k = 0; k < 5; ++k)
            {
                if (fields[i][j][k] != -1)
                {
                    winner_horizontal = false;
                    if (!winner_vertical) break;
                }
                if (fields[i][k][j] != -1)
                {
                    winner_vertical = false;
                    if (!winner_horizontal) break;
                }
            }
            if (winner_horizontal || winner_vertical)
            {
                if (fields.size() != 1)
                    fields.erase(fields.begin() + i);
                win = true;
            }
        }
    }
    return win;
}

int score(vector<vector<vector<int>>> const &fields, int last)
{
    int total = 0;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if(fields[0][i][j] != -1)
                total += fields[0][i][j];
        }
    }
    return total * last;
}

