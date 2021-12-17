#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>
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

    unordered_set<int> possible_x;
    unordered_set<int> possible_y;

    for (int i = 0; i <= x2; ++i)
    {
        for (int j = i, k = 0, sum = i; k < i; --j, sum += j, ++k)
            if (sum >= x1 && sum <= x2)
                possible_x.insert(i);
    }

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

    for (int i = 0; i >= y1; --i)
    {
        for (int j = i, sum = i; sum >= y1; --j, sum += j)
            if (sum >= y1 && sum <= y2)
                possible_y.insert(i);
    }

    int total = 0;

    for (int x : possible_x)
    {
        for (int y : possible_y)
        {
            for (int i = 0, k = 0, a = x, b = y; i <= x2 && k >= y1; a = (a == 0 ? 0 : a - 1), --b)
            {
                if (a == 0 && i < x1)
                    break;
                if (i >= x1 && i <= x2 && k >= y1 && k <= y2)
                {
                    ++total;
                    break;
                }
                i += a;
                k += b;
            }
        }
    }

    cout << total << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}