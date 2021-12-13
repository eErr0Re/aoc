#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<char> find_correct_wiring(vector<string>);
vector<char> diff(const vector<char> &, const string &);
vector<char> verify(const vector<vector<char>> &, const vector<string> &);
int decode(const vector<char> &, const string &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    vector<string> signals(10);
    int count = 0;

    while (!in.eof())
    {
        for (int i = 0; i < 10; ++i)
            in >> signals[i];

        vector<char> wiring = find_correct_wiring(signals);

        string s;
        in >> s;
        for (int i = 3; i >= 0; --i)
        {
            in >> s;
            count += decode(wiring, s) * pow(10, i);
        }
    }

    cout << count << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";   
}

vector<char> find_correct_wiring(vector<string> signals)
{
    sort(signals.begin(), signals.end(), [](string a, string b) { return a.size() < b.size(); });
    vector<vector<char>> combinations;

    for (const string &s : signals)
    {
        switch (s.size())
        {
            case 2:
            {
                vector<char> wiring(7, ' ');
                wiring[1] = s[0];
                wiring[2] = s[1];
                combinations.push_back(wiring);
                wiring[1] = s[1];
                wiring[2] = s[0];
                combinations.push_back(wiring);
                break;
            }
            case 3:
            {
                vector<char> d = diff(combinations[0], s);
                combinations[0][0] = d[0];
                combinations[1][0] = d[0];
                break;
            }
            case 4:
            {
                vector<char> d = diff(combinations[0], s);
                combinations.push_back(combinations[0]);
                combinations.push_back(combinations[1]);
                for (int i = 0; i < 2; ++i)
                {
                    combinations[i][5] = d[0];
                    combinations[i][6] = d[1];
                    combinations[i + 2][5] = d[1];
                    combinations[i + 2][6] = d[0];
                }
                break;
            }
            case 5:
            {
                vector<char> d = diff(combinations[0], s);
                if (d.size() > 1 || combinations[0][3] != ' ') break;
                for (vector<char> &c : combinations)
                    c[3] = d[0];
                break;
            }
            case 6:
            {
                vector<char> d = diff(combinations[0], s);
                if (d.empty() || combinations[0][4] != ' ') break;
                for (vector<char> &c : combinations)
                    c[4] = d[0];
            }
        }
    }
    return verify(combinations, signals);
}

vector<char> diff(const vector<char> &wiring, const string &signal)
{
    vector<char> diff;

    for (char c : signal)
        if (find(wiring.cbegin(), wiring.cend(), c) == wiring.cend())
            diff.push_back(c);

    return diff;
}

vector<char> verify(const vector<vector<char>> &combinations, const vector<string> &signals)
{
    for (const vector<char> &c : combinations)
    {
        bool found = true;
        for (const string &s : signals)
        {
            if (decode(c, s) == -1)
            {
                found = false;
                break;
            }
        }
        if (found) return c;
    }
    return vector<char>();
}

int decode(const vector<char> &wiring, const string &signal)
{
    if (signal.size() == 2) return 1;
    if (signal.size() == 3) return 7;
    if (signal.size() == 4) return 4;
    if (signal.size() == 7) return 8;

    vector<int> indxs;
    for (int i = 0; i < wiring.size(); ++i)
        if (signal.find(wiring[i]) != string::npos)
            indxs.push_back(i);
        
    if (indxs == vector<int>({0,1,3,4,6})) return 2;
    if (indxs == vector<int>({0,1,2,3,6})) return 3;
    if (indxs == vector<int>({0,2,3,5,6})) return 5;
    if (indxs == vector<int>({0,2,3,4,5,6})) return 6;
    if (indxs == vector<int>({0,1,2,3,5,6})) return 9;
    if (indxs == vector<int>({0,1,2,3,4,5})) return 0;

    return -1;
}