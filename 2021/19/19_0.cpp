#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// sry :(
const int DIR[24][6] =
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
    for (auto it = absolute.begin(); it != absolute.end(); ++it)
    {
        for (int i = 0; i < 24; ++i)
        {
            for (position p : relative)
            {
                int count = 0;
                auto offset = p;
                int x = DIR[i][0] == 0 ? p.x : (DIR[i][0] == 1 ? p.y : p.z);
                int y = DIR[i][1] == 0 ? p.x : (DIR[i][1] == 1 ? p.y : p.z);
                int z = DIR[i][2] == 0 ? p.x : (DIR[i][2] == 1 ? p.y : p.z);
                offset.x =  DIR[i][3] * x - (*it).x;
                offset.y = DIR[i][4] * y - (*it).y;
                offset.z = DIR[i][5] * z - (*it).z;

                for (position p : relative)
                {

                    auto pos = p;
                    int x = DIR[i][0] == 0 ? p.x : (DIR[i][0] == 1 ? p.y : p.z);
                    int y = DIR[i][1] == 0 ? p.x : (DIR[i][1] == 1 ? p.y : p.z);
                    int z = DIR[i][2] == 0 ? p.x : (DIR[i][2] == 1 ? p.y : p.z);
                    
                    pos.x = DIR[i][3] * x - offset.x;
                    pos.y = DIR[i][4] * y - offset.y;
                    pos.z = DIR[i][5] * z - offset.z;
                    
                    if (absolute.find(pos) != absolute.end())
                        ++count;
                }

                if (count >= 12)
                {  
                    for (position p : relative)
                    {
                        auto pos = p;
                        int x = DIR[i][0] == 0 ? p.x : (DIR[i][0] == 1 ? p.y : p.z);
                        int y = DIR[i][1] == 0 ? p.x : (DIR[i][1] == 1 ? p.y : p.z);
                        int z = DIR[i][2] == 0 ? p.x : (DIR[i][2] == 1 ? p.y : p.z);
                        
                        pos.x = DIR[i][3] * x - offset.x;
                        pos.y = DIR[i][4] * y - offset.y;
                        pos.z = DIR[i][5] * z - offset.z;

                        absolute.insert(pos);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}