#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream in("input.txt");
    vector<vector<int>> field(1000, vector<int>(1000, 0));
    int x1, y1, x2, y2;
    char c;
    string s;
    while (in >> x1 >> c >> y1 >> s >> x2 >> c >> y2)
    {
        bool x_asc = x2 > x1;
        bool y_asc = y2 > y1;

        if (x1 != x2 && y1 != y2)
        {
            while ((x_asc ? x1 <= x2 : x2 <= x1) && (y_asc ? y1 <= y2 : y2 <= y1))
            {
                ++field[y1][x1];
                x_asc ? ++x1 : --x1;
                y_asc ? ++y1 : --y1;
            }
        }
        else if (x1 != x2)
        {
            while (x_asc ? x1 <= x2 : x2 <= x1)
            {
                ++field[y1][x1];
                x_asc ? ++x1 : --x1;
            }
        }
        else
        {
            while (y_asc ? y1 <= y2 : y2 <= y1)
            {
                ++field[y1][x1];
                y_asc ? ++y1 : --y1;
            }
        }
    }

    int count = 0;

    for (vector<int> row : field)
        for (int val : row)
            if (val >= 2) ++count;

    cout << count << endl;
}