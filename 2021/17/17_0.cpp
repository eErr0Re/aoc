#include <iostream>
#include <fstream>
#include <chrono>
#include <set>
#include <cmath>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string s;
    char c;
    int x1, x2, y1, y2;
    in >> s >> s >> c >> c;
    in >> x1 >> c >> c >> x2 >> c >> c >> c;
    in >> y1 >> c >> c >> y2;

    set<int> possible_x;
    set<int> possible_y;

    for (int i = y1; i <= y2; ++i)
    {
        for (int j = 0; ; ++j)
        {
            int a = -j - 1;
            double val = 0.5 - sqrt(0.25 - 2 * i + pow(a, 2) + a);
            if ((int) val - val < numeric_limits<double>::epsilon())
                possible_y.insert(j);

            if (val < i)
                break;
        }
    }

    int y = *possible_y.crbegin();
    cout << y * (y + 1) / 2 << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}