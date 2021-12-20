#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string algorithm, line;
    in >> algorithm >> line;
    unsigned sz = line.size() + 2;

    vector<vector<bool>> grid;
    grid.push_back(vector<bool>(sz, 0));

    do
    {
        vector<bool> ln;
        ln.reserve(sz);
        ln.push_back(0);

        for (char c : line)
            ln.push_back(c == '.' ? 0 : 1);

        ln.push_back(0);
        grid.push_back(ln);
    } while (in >> line);

    grid.push_back(vector<bool>(sz, 0));

    bool inf = 0;

    for (unsigned i = 0; i < 50; ++i)
    {
        bool new_inf = algorithm[inf ? 511 : 0] == '.' ? 0 : 1;
        sz += 2;
        vector<vector<bool>> temp;
        temp.push_back(vector<bool>(sz, new_inf));

        for (int r = 0; r < grid.size(); ++r)
        {
            vector<bool> row;
            row.reserve(sz);
            row.push_back(new_inf);

            for (int c = 0; c < sz - 2; ++c)
            {
                string index;

                // Top left
                if (r - 1 >= 0 && c - 1 >= 0)
                    index += grid[r - 1][c - 1] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Top mid
                if (r - 1 >= 0)
                    index += grid[r - 1][c] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Top right
                if (r - 1 >= 0 && c + 1 < sz - 2)
                    index += grid[r - 1][c + 1] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Mid left
                if (c - 1 >= 0)
                    index += grid[r][c - 1] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Mid mid
                index += grid[r][c] ? '1' : '0';

                // Mid right
                if (c + 1 < sz - 2)
                    index += grid[r][c + 1] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Bottom left
                if (r + 1 < grid.size() && c - 1 >= 0)
                    index += grid[r + 1][c - 1] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Bottom mid
                if (r + 1 < grid.size())
                    index += grid[r + 1][c] ? '1' : '0';
                else index += inf ? '1' : '0';

                // Bottom right
                if (r + 1 < grid.size() && c + 1 < sz - 2)
                    index += grid[r + 1][c + 1] ? '1' : '0';
                else index += inf ? '1' : '0';

                // cout << index << endl;
                row.push_back(algorithm[stoi(index, 0, 2)] == '.' ? 0 : 1);
            }
            row.push_back(new_inf);
            temp.push_back(row);
        }
        temp.push_back(vector<bool>(sz, new_inf));
        grid = temp;
        inf = new_inf;
    }

    int count = 0;
    for (const vector<bool> &row : grid)
        for (bool pixel : row)
            count += pixel;

    cout << count << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}