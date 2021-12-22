#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct position
{
    int x, y, z;
    bool deleted = false;

    bool operator==(const position &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string action;
    char c;
    int x1, x2, y1, y2, z1, z2;

    vector<pair<position, position>> on_cubes;

    while (in >> action >> c >> c >> x1 >> c >> c >> x2 >> c >> c >> c >> 
        y1 >> c >> c >> y2 >> c >> c >> c >> z1 >> c >> c >> z2)
    {
        pair<position, position> area = { { x1, y1, z1 }, { x2, y2, z2 } };

        size_t sz = on_cubes.size();
        for (size_t i = 0; i < sz; ++i)
        {
            if (on_cubes[i].first.deleted)
                continue;
            pair<position, position> on = on_cubes[i];
            if (area.first.x <= on.second.x && area.second.x >= on.first.x
                && area.first.y <= on.second.y && area.second.y >= on.first.y
                && area.first.z <= on.second.z && area.second.z >= on.first.z)
            {
                if (area.second.y < on.second.y)
                    on_cubes.push_back({ {on.first.x, area.second.y + 1, on.first.z}, on.second });
                if (area.first.y > on.first.y)
                    on_cubes.push_back({ on.first, { on.second.x, area.first.y - 1, on.second.z} });
                if (area.second.z < on.second.z)
                    on_cubes.push_back({ { on.first.x, max(area.first.y, on.first.y), area.second.z + 1 }, { on.second.x, min(area.second.y, on.second.y), on.second.z } });
                if (area.first.z > on.first.z)
                    on_cubes.push_back({ { on.first.x, max(area.first.y, on.first.y), on.first.z }, { on.second.x, min(area.second.y, on.second.y), area.first.z - 1 } });
                if (area.second.x < on.second.x)
                    on_cubes.push_back({ { area.second.x + 1, max(area.first.y, on.first.y), max(area.first.z, on.first.z) }, { on.second.x, min(area.second.y, on.second.y), min(area.second.z, on.second.z) } });
                if (area.first.x > on.first.x)
                    on_cubes[i] = { { on.first.x, max(area.first.y, on.first.y), max(area.first.z, on.first.z) }, { area.first.x - 1, min(area.second.y, on.second.y), min(area.second.z, on.second.z) } };
                else on_cubes[i].first.deleted = true;
            }
        }

        if (action == "on")
            on_cubes.push_back(area);
    }

    unsigned long long count = 0;
    for (const pair<position, position> &on : on_cubes)
    {
        if (on.first.deleted)
            continue;
        count += (abs(on.first.x - on.second.x) + 1ull) * (abs(on.first.y - on.second.y) + 1) * (abs(on.first.z - on.second.z) + 1);
    }

    cout << count << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}