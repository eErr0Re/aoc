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

bool findOverlap(pair<unordered_set<position>, unordered_set<position>> &, const pair<unordered_set<position>, unordered_set<position>> &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string s;
    int x, y, z;
    char c;

    vector<pair<unordered_set<position>, unordered_set<position>>> scanners;
    
    int i = 0;
    while (getline(in, s))
    {
        unordered_set<position> scanner;

        while (in >> x >> c >> y >> c >> z)
            scanner.insert({ x, y, z });

        scanners.push_back({ scanner, {{ 0, 0, 0 }}});

        in.clear();

        ++i;
    }

    pair<unordered_set<position>, unordered_set<position>> beacons = scanners[0];

    while (!scanners.empty())
    {
        vector<pair<unordered_set<position>, unordered_set<position>>> temp;
        for (pair<unordered_set<position>, unordered_set<position>> scanner : scanners)
            if (!findOverlap(beacons, scanner))
                temp.push_back(scanner);

        scanners = temp;
    }

    int max = 0;
    vector<position> scanner_positions(beacons.second.cbegin(), beacons.second.cend());
    for (auto it1 = scanner_positions.cbegin(); it1 != scanner_positions.cend(); ++it1)
    {
        for (auto it2 = it1 + 1; it2 != scanner_positions.cend(); ++it2)
        {
            int dist = abs((*it1).x - (*it2).x) + abs ((*it1).y - (*it2).y) + abs((*it1).z - (*it2).z);
            if (dist > max) max = dist; 
        }
    }

    cout << max << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

bool findOverlap(pair<unordered_set<position>, unordered_set<position>> &absolute, const pair<unordered_set<position>, unordered_set<position>> &relative)
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

    for (const position &abs : absolute.first)
    {
        for (int i = 0; i < 24; ++i)
        {
            for (position offset : relative.first)
            {
                int count = 0;

                int x = dir[i][0] == 0 ? offset.x : (dir[i][0] == 1 ? offset.y : offset.z);
                int y = dir[i][1] == 0 ? offset.x : (dir[i][1] == 1 ? offset.y : offset.z);
                int z = dir[i][2] == 0 ? offset.x : (dir[i][2] == 1 ? offset.y : offset.z);

                offset.x =  dir[i][3] * x - abs.x;
                offset.y = dir[i][4] * y - abs.y;
                offset.z = dir[i][5] * z - abs.z;

                for (position pos : relative.first)
                {
                    int x = dir[i][0] == 0 ? pos.x : (dir[i][0] == 1 ? pos.y : pos.z);
                    int y = dir[i][1] == 0 ? pos.x : (dir[i][1] == 1 ? pos.y : pos.z);
                    int z = dir[i][2] == 0 ? pos.x : (dir[i][2] == 1 ? pos.y : pos.z);
                    
                    pos.x = dir[i][3] * x - offset.x;
                    pos.y = dir[i][4] * y - offset.y;
                    pos.z = dir[i][5] * z - offset.z;
                    
                    if (absolute.first.find(pos) != absolute.first.end())
                        ++count;
                }

                if (count >= 12)
                {  
                    for (position pos : relative.first)
                    {
                        int x = dir[i][0] == 0 ? pos.x : (dir[i][0] == 1 ? pos.y : pos.z);
                        int y = dir[i][1] == 0 ? pos.x : (dir[i][1] == 1 ? pos.y : pos.z);
                        int z = dir[i][2] == 0 ? pos.x : (dir[i][2] == 1 ? pos.y : pos.z);
                        
                        pos.x = dir[i][3] * x - offset.x;
                        pos.y = dir[i][4] * y - offset.y;
                        pos.z = dir[i][5] * z - offset.z;

                        absolute.first.insert(pos);
                    }
                    
                    for (position p : relative.second)
                        absolute.second.insert({ p.x - offset.x, p.y - offset.y, p.z - offset.z });

                    return true;
                }
            }
        }
    }
    return false;
}