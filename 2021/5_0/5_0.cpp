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
        if (x1 != x2 && y1 != y2)
            continue;

        if (x1 != x2)
        {
            int x = x1 < x2 ? x1 : x2;
            if (x != x1) x2 = x1;

            while (x <= x2)
                ++field[y1][x++];
        }
        else
        {
            int y = y1 < y2 ? y1 : y2;
            if (y != y1) y2 = y1;

            while (y <= y2)
                ++field[y++][x1];
        }
    }

    int count = 0;

    for (vector<int> row : field)
        for (int val : row)
            if (val >= 2) ++count;

    cout << count << endl;
}