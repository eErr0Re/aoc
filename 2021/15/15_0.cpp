#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

struct pos
{
    int y, x, priority, val;
};

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string line;
    vector<vector<int>> map;
    
    while (in >> line)
    {
        vector<int> row;
        for (char c : line)
            row.push_back(c - '0');
        map.push_back(row);
    }

    vector<vector<int>> paths(map.size(), vector<int>(map.size(), -1));
    queue<pos> queue;
    queue.push({0, 0, 1, 0});

    while (1)
    {
        pos current = queue.front();
        queue.pop();

        if (paths[current.y][current.x] != -1)
            continue;

        if (current.priority > 1)
        {
            --current.priority;
            queue.push(current);
            continue;
        }

        paths[current.y][current.x] = current.val;
        if (current.y == map.size() - 1 && current.x == map.size() - 1)
            break;

        if (current.y - 1 >= 0)
            queue.push({current.y - 1, current.x, map[current.y - 1][current.x], current.val + map[current.y - 1][current.x]});
        if (current.y + 1 < map.size())
            queue.push({current.y + 1, current.x, map[current.y + 1][current.x], current.val + map[current.y + 1][current.x]});
        if (current.x - 1 >= 0)
            queue.push({current.y, current.x - 1, map[current.y][current.x - 1], current.val + map[current.y][current.x - 1]});
        if (current.x + 1 < map.size())
            queue.push({current.y, current.x + 1, map[current.y][current.x + 1], current.val + map[current.y][current.x + 1]});
    }
    
    cout << paths.back().back() << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}