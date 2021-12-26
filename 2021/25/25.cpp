// TOO SLOW
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int solve(vector<vector<char>>, vector<char>);
bool is_correct(const vector<char> &, char);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    vector<string> map;
    string row;

    while (in >> row)
        map.push_back(row);
        
    int steps = 0;
    bool moved;
    do
    {
        ++steps;
        moved = false;

        // East
        for (string &row : map)
        {
            bool first_moved = false;
            for (auto it = row.begin(); it != row.end(); ++it)
            {
                if (*it != '>')
                    continue;

                if (it == row.end() - 1)
                {
                    if (*row.begin() == '.' && !first_moved)
                    {
                        moved = true;
                        *row.begin() = '>';
                        *it = '.';
                    }
                    continue;
                }

                if (*(it + 1) == '.')
                {
                    moved = true;
                    if (it == row.begin())
                        first_moved = true;
                    *it = '.';
                    *(it + 1) = '>';
                    ++it;
                }
            }
        }

        // South
        for (int i = 0; i < map[0].size(); ++i)
        {
            bool first_moved = false;
            for (auto it = map.begin(); it != map.end(); ++it)
            {
                if ((*it)[i] != 'v')
                    continue;

                if (it == map.end() - 1)
                {
                    if ((*map.begin())[i] == '.' && !first_moved)
                    {
                        moved = true;
                        (*map.begin())[i] = 'v';
                        (*it)[i] = '.';
                    }
                    continue;
                }

                if ((*(it + 1))[i] == '.')
                {
                    moved = true;
                    if (it == map.begin())
                        first_moved = true;
                    (*it)[i] = '.';
                    (*(it + 1))[i] = 'v';
                    ++it;
                }
            }
        }

    } while (moved);

    cout << steps << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}
