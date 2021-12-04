#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int solve(vector<vector<vector<int>>> &, int);
int check(vector<vector<vector<int>>> const &);
int score(vector<vector<vector<int>>> const &, int, int);

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

    int winner = -1;
    int last;
    for (int i = 0; i < values.size() && winner < 0; ++i)
    {
        winner = solve(fields, values[i]);
        last = values[i];
    }
    cout << score(fields, winner, last) << endl;
}

int solve(vector<vector<vector<int>>> &fields, int val)
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

int check(vector<vector<vector<int>>> const &fields)
{
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
            if (winner_horizontal || winner_vertical) return i;
        }
    }
    return -1;
}

int score(vector<vector<vector<int>>> const &fields, int winner, int last)
{
    int total = 0;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if(fields[winner][i][j] != -1)
                total += fields[winner][i][j];
        }
    }
    return total * last;
}

