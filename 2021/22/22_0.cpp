#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string action;
    char c;
    int x1, x2, y1, y2, z1, z2;

    bool cube[101][101][101] = { 0 };

    int count = 0;
    while (in >> action >> c >> c >> x1 >> c >> c >> x2 >> c >> c >> c >> 
        y1 >> c >> c >> y2 >> c >> c >> c >> z1 >> c >> c >> z2)
    {
        for (int x = max(-50, x1) + 50; x < min(50, x2) + 51; ++x)
            for (int y = max(-50, y1) + 50; y < min(50, y2) + 51; ++y)
                for (int z = max(-50, z1) + 50; z < min(50, z2) + 51; ++z)
                {
                    bool on = action == "on" ? 1 : 0;
                    if (cube[x][y][z] != on)
                    {
                        if (on) ++count;
                        else --count;
                    }
                    cube[x][y][z] = on;
                }
    }

    cout << count << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}