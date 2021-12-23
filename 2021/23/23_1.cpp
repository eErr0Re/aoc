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
    string line;
    vector<vector<char>> rooms(4, vector<char>(4, '.'));
    vector<char> hallway(11, '.');
    in >> line >> line >> line;
    for (int i = 0; i < rooms.size(); ++i)
        rooms[i][0] = line[3 + 2 * i];

    for (int i = 1; i < rooms[0].size(); ++i)
    {
        in >> line;
        for (int j = 0; j < rooms.size(); ++j)
            rooms[j][i] = line[1 + 2 * j];
    }


    cout << solve(rooms, hallway) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

int solve(vector<vector<char>> rooms, vector<char> hallway)
{
    static const int val[] = { 1, 10, 100, 1000 };

    int min = INT_MAX;
    
    bool solved = true;
    for (int i = 0; i < rooms.size(); ++i)
    {
        if (!is_correct(rooms[i], 'A' + i) || rooms[i][0] == '.')
            solved = false;
        if (!solved) break;
    }
    if (solved)
        return 0;
    
    for (int i = 0; i < rooms.size(); ++i)
    {
        if (!is_correct(rooms[i], 'A' + i))
            continue;

        if (rooms[i][0] != '.')
            continue;

        int index = 0;
        for (char c : rooms[i])
        {
            if (c == '.')
                ++index;
            else break;;
        }
        --index;

        for (int j = i * 2 + 3; j < 11; ++j)
        {
            if (hallway[j] == '.')
                continue;
            if (hallway[j] != 'A' + i)
                break;
            if (j == 2 || j == 4 || j == 6 || j == 8)
                continue;
            vector<vector<char>> new_rooms = rooms;
            vector<char> new_hallway = hallway;
            new_rooms[i][index] = 'A' + i;
            new_hallway[j] = '.';
            int energy = solve(new_rooms, new_hallway);
            if (energy == INT_MAX)
                return min;
            energy += val[i] * (j - (i * 2 + 2) + index + 1);
            if (energy < min) min = energy;
            return min;
        }

        for (int j = i * 2 + 1; j >= 0; --j)
        {
            if (hallway[j] == '.')
                continue;
            if (hallway[j] != 'A' + i)
                break;
            if (j == 2 || j == 4 || j == 6 || j == 8)
                continue;
            vector<vector<char>> new_rooms = rooms;
            vector<char> new_hallway = hallway;
            new_rooms[i][index] = 'A' + i;
            new_hallway[j] = '.';
            int energy = solve(new_rooms, new_hallway);
            if (energy == INT_MAX)
                return min;
            energy += val[i] * ((i * 2 + 2) - j + index + 1);
            if (energy < min) min = energy;
            return min;
        }
    }

    for (int i = 0; i < rooms.size(); ++i)
    {
        if (is_correct(rooms[i], 'A' + i))
            continue;

        int index = 0;
        for (char c : rooms[i])
        {
            if (c == '.')
                ++index;
            else break;
        }

        for (int j = i * 2 + 3; j < 11; ++j)
        {
            if (hallway[j] != '.')
                break;
            if (j == 2 || j == 4 || j == 6 || j == 8)
                continue;
            vector<vector<char>> new_rooms = rooms;
            vector<char> new_hallway = hallway;
            new_rooms[i][index] = '.';
            new_hallway[j] = rooms[i][index];
            int energy = solve(new_rooms, new_hallway);
            if (energy == INT_MAX)
                continue;
            energy += val[rooms[i][index] - 'A'] * (j - (i * 2 + 2) + index + 1);
            if (energy < min) min = energy;
        }

        for (int j = i * 2 + 1; j >= 0; --j)
        {
            if (hallway[j] != '.')
                break;
            if (j == 2 || j == 4 || j == 6 || j == 8)
                continue;
            vector<vector<char>> new_rooms = rooms;
            vector<char> new_hallway = hallway;
            new_rooms[i][index] = '.';
            new_hallway[j] = rooms[i][index];
            int energy = solve(new_rooms, new_hallway);
            if (energy == INT_MAX)
                continue;
            energy += val[rooms[i][index] - 'A'] * ((i * 2 + 2) - j + index + 1);
            if (energy < min) min = energy;
        }
    }
    return min;
}

bool is_correct(const vector<char> &room, char correct)
{
    for (char c : room)
        if (c != correct && c != '.')
            return false;
    return true;
}