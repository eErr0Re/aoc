#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    int x, y;
    char c;
    vector<vector<bool>> paper;
    int max_x = 0;

    while (in >> x >> c >> y)
    {
        for (int i = paper.size() - 1; i < y; ++i)
            paper.push_back(vector<bool>());

        for (int i = paper[y].size() - 1; i < x; ++i)
            paper[y].push_back(0);

        paper[y][x] = 1;

        if (x > max_x) max_x = x;
    }

    in.clear();

    string a;
    char dir;
    int val;
    in >> a >> a >> dir >> c >> val;

    int y_size = paper.size();
    int x_size = max_x + 1;

    if (dir == 'y')
    {
        for (int i = 0, k = y_size - 1; i != val && k != val; ++i, --k)
        {
            for (int j = 0; j < paper[k].size(); ++j)
            {
                if (j >= paper[i].size())
                    paper[i].push_back(paper[k][j]);
                else paper[i][j] = paper[i][j] | paper[k][j];
            }
        }
        y_size -= val;
    }

    if (dir == 'x')
    {
        for (int i = 0; i < y_size; ++i)
        {
            for (int j = 0, k = x_size - 1; j != val && k != val; ++j, --k)
            {
                if (k >= paper[i].size())
                    continue;
                paper[i][j] = paper[i][j] | paper[i][k];
            }
        }
        x_size -= val;
    }

    int count = 0;
    for (int i = 0; i < y_size; ++i)
        for (int j = 0; j < x_size && j < paper[i].size(); ++j)
            if (paper[i][j]) ++count;
    
    cout << count << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}