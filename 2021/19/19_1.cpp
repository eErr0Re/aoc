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
    for (auto it = absolute.first.begin(); it != absolute.first.end(); ++it)
    {
        for (int i = 0; i < 24; ++i)
        {
            for (position p : relative.first)
            {
                int count = 0;
                auto offset = p;
                int x = DIR[i][0] == 0 ? p.x : (DIR[i][0] == 1 ? p.y : p.z);
                int y = DIR[i][1] == 0 ? p.x : (DIR[i][1] == 1 ? p.y : p.z);
                int z = DIR[i][2] == 0 ? p.x : (DIR[i][2] == 1 ? p.y : p.z);
                offset.x =  DIR[i][3] * x - (*it).x;
                offset.y = DIR[i][4] * y - (*it).y;
                offset.z = DIR[i][5] * z - (*it).z;

                for (position p : relative.first)
                {
                    auto pos = p;
                    int x = DIR[i][0] == 0 ? p.x : (DIR[i][0] == 1 ? p.y : p.z);
                    int y = DIR[i][1] == 0 ? p.x : (DIR[i][1] == 1 ? p.y : p.z);
                    int z = DIR[i][2] == 0 ? p.x : (DIR[i][2] == 1 ? p.y : p.z);
                    
                    pos.x = DIR[i][3] * x - offset.x;
                    pos.y = DIR[i][4] * y - offset.y;
                    pos.z = DIR[i][5] * z - offset.z;
                    
                    if (absolute.first.find(pos) != absolute.first.end())
                        ++count;
                }

                if (count >= 12)
                {  
                    for (position p : relative.first)
                    {
                        auto pos = p;
                        int x = DIR[i][0] == 0 ? p.x : (DIR[i][0] == 1 ? p.y : p.z);
                        int y = DIR[i][1] == 0 ? p.x : (DIR[i][1] == 1 ? p.y : p.z);
                        int z = DIR[i][2] == 0 ? p.x : (DIR[i][2] == 1 ? p.y : p.z);
                        
                        pos.x = DIR[i][3] * x - offset.x;
                        pos.y = DIR[i][4] * y - offset.y;
                        pos.z = DIR[i][5] * z - offset.z;

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