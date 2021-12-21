#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;

void roll(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, 
    bool, pair<unsigned long long, unsigned long long> &, unsigned long long = 1);

unsigned short move(unsigned short, unsigned short);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string s;
    unsigned short a, b;
    in >> s >> s >> s >> s >> a;
    in >> s >> s >> s >> s >> b;

    pair<unsigned long long, unsigned long long> wins = { 0, 0 };

    for (unsigned short i = 3; i <= 9; ++i)
        roll(a, 0, b, 0, i, true, wins);

    cout << max(wins.first, wins.second) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

void roll(unsigned short a, unsigned short score_a, unsigned short b, unsigned short score_b, unsigned short rolled, 
    bool a_rolled, pair<unsigned long long, unsigned long long> &wins, unsigned long long universes)
{
    if (rolled == 4 || rolled == 8)
        universes *= 3;
    if (rolled == 5 || rolled == 7)
        universes *= 6; 
    if (rolled == 6)
        universes *= 7;

    if (a_rolled)
    {
        a = move(a, rolled);
        score_a += a;

        if (score_a >= 21)
        {
            wins.first += universes;
            return;
        }

        for (unsigned short i = 3; i <= 9; ++i)
            roll(a, score_a, b, score_b, i, false, wins, universes);
    }
    else
    {
        b = move(b, rolled);
        score_b += b;
        
        if (score_b >= 21)
        {
            wins.second += universes;
            return;
        }

        for (unsigned short i = 3; i <= 9; ++i)
            roll(a, score_a, b, score_b, i, true, wins, universes);
    }
}

unsigned short move(unsigned short pos, unsigned short rolled)
{
    pos = (pos + rolled) % 10;
    if (!pos) pos = 10;
    return pos;
}