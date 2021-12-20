#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct position
{
    int x, y, z;

    bool operator==(const position &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

template<>
struct std::hash<position>
{
    size_t operator()(const position &p) const
    {
        return (size_t) p.x * 17 * 17 + p.y * 17 + p.z;
    }
};

bool findOverlap(unordered_set<position> &, const unordered_set<position> &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string s;
    int x, y, z;
    char c;

    vector<unordered_set<position>> scanners;
    
    int i = 0;
    while (getline(in, s))
    {
        scanners.push_back(unordered_set<position>());

        while (in >> x >> c >> y >> c >> z)
            scanners[i].insert({ x, y, z });

        in.clear();

        ++i;
    }
    
    unordered_set<position> beacons = scanners[0];

    while (!scanners.empty())
    {
        vector<unordered_set<position>> temp;
        for (unordered_set<position> scanner : scanners)
            if (!findOverlap(beacons, scanner))
                temp.push_back(scanner);
        scanners = temp;
    }

    cout << beacons.size() << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

bool findOverlap(unordered_set<position> &absolute, const unordered_set<position> &relative)
{
    // sry :(
    static const int dir[24][6] =
    {
        { 0, 1, 2, 1, 1, 1 },
        { 0, 1, 2, 1, -1, -1 },
        { 0, 1, 2, -1, 1, -1 },
        { 0, 1, 2, -1, -1, 1 },
        { 0, 2, 1, 1, -1, 1 },
        { 0, 2, 1, 1, 1, -1 },
        { 0, 2, 1, -1, -1, -1 },
        { 0, 2, 1, -1, 1, 1 },
        { 1, 0, 2, -1, 1, 1 },
        { 1, 0, 2, -1, -1, -1 },
        { 1, 0, 2, 1, 1, -1 },
        { 1, 0, 2, 1, -1, 1 },
        { 1, 2, 0, 1, -1, -1 },
        { 1, 2, 0, 1, 1, 1 },
        { 1, 2, 0, -1, -1, 1 },
        { 1, 2, 0, -1, 1, -1 },
        { 2, 0, 1, 1, -1, -1 },
        { 2, 0, 1, 1, 1, 1 },
        { 2, 0, 1, -1, -1, 1 },
        { 2, 0, 1, -1, 1, -1 },
        { 2, 1, 0, 1, 1, -1 },
        { 2, 1, 0, 1, -1, 1 },
        { 2, 1, 0, -1, 1, 1 },
        { 2, 1, 0, -1, -1, -1 }
    };

    for (const position &abs : absolute)
    {
        for (int i = 0; i < 24; ++i)
        {
            for (position offset : relative)
            {
                int count = 0;

                int x = dir[i][0] == 0 ? offset.x : (dir[i][0] == 1 ? offset.y : offset.z);
                int y = dir[i][1] == 0 ? offset.x : (dir[i][1] == 1 ? offset.y : offset.z);
                int z = dir[i][2] == 0 ? offset.x : (dir[i][2] == 1 ? offset.y : offset.z);

                offset.x =  dir[i][3] * x - abs.x;
                offset.y = dir[i][4] * y - abs.y;
                offset.z = dir[i][5] * z - abs.z;

                for (position pos : relative)
                {
                    int x = dir[i][0] == 0 ? pos.x : (dir[i][0] == 1 ? pos.y : pos.z);
                    int y = dir[i][1] == 0 ? pos.x : (dir[i][1] == 1 ? pos.y : pos.z);
                    int z = dir[i][2] == 0 ? pos.x : (dir[i][2] == 1 ? pos.y : pos.z);
                    
                    pos.x = dir[i][3] * x - offset.x;
                    pos.y = dir[i][4] * y - offset.y;
                    pos.z = dir[i][5] * z - offset.z;
                    
                    if (absolute.find(pos) != absolute.end())
                        ++count;
                }

                if (count >= 12)
                {  
                    for (position pos : relative)
                    {
                        int x = dir[i][0] == 0 ? pos.x : (dir[i][0] == 1 ? pos.y : pos.z);
                        int y = dir[i][1] == 0 ? pos.x : (dir[i][1] == 1 ? pos.y : pos.z);
                        int z = dir[i][2] == 0 ? pos.x : (dir[i][2] == 1 ? pos.y : pos.z);
                        
                        pos.x = dir[i][3] * x - offset.x;
                        pos.y = dir[i][4] * y - offset.y;
                        pos.z = dir[i][5] * z - offset.z;

                        absolute.insert(pos);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}