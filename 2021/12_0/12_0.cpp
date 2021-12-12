#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int find_paths(const unordered_map<string, vector<string>> &, unordered_set<string>, const string &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string line;
    unordered_map<string, vector<string>> paths;

    while (in >> line)
    {
        int i = line.find("-");
        string left = line.substr(0, i);
        string right = line.substr(i + 1, line.size());
        paths[left].push_back(right);
        paths[right].push_back(left);
    }

    unordered_set<string> visited;
    int result = find_paths(paths, visited, "start");

    cout << result << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

int find_paths(const unordered_map<string, vector<string>> &paths, unordered_set<string> visited, const string &start)
{
    if (visited.find(start) != visited.end() && !isupper(start[0])) return 0;
    if (start == "end") return 1;
    visited.insert(start);

    int result = 0;

    for (const string &cave : paths.at(start))
        result += find_paths(paths, visited, cave);

    return result;
}