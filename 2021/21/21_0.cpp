#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;

void roll(unsigned short &, unsigned short &, unsigned short &, unsigned short &, unsigned short &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string s;
    unsigned short a, b;
    in >> s >> s >> s >> s >> a;
    in >> s >> s >> s >> s >> b;

    unsigned short score_a = 0, score_b = 0, times_rolled = 0, first = 1, second = 2, third = 3;

    while (score_a < 1000 && score_b < 1000)
    {
        roll(a, score_a, first, second, third);
        times_rolled += 3;

        if (score_a >= 1000)
            break;

        roll(b, score_b, first, second, third);
        times_rolled += 3;
    }

    cout << min(score_a, score_b) * times_rolled << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

void roll(unsigned short &pos, unsigned short &score, unsigned short &first, unsigned short &second, unsigned short &third)
{
    pos = (pos + first + second + third) % 10;
    if (!pos) pos = 10;
    score += pos;

    first = (first + 3) % 100;
    if (!first) first = 100;
    second = (second + 3) % 100;
    if (!second) second = 100;
    third = (third + 3) % 100;
    if (!third) third = 100;
}