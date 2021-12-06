#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <set>
using namespace std;

int DAYS = 256;

void count(int, map<int, size_t> &, map<int, size_t> &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    int n;
    char c;
    size_t cnt = 0;
    map<int, size_t> ages;
    map<int, size_t> nr_of_children;
    set<int> start_ages;

    while (in >> n)
    {
        ++ages[n];

        if (ages[n] == 1)
            count(n, ages, nr_of_children);

        ++cnt;
        start_ages.insert(n);
        in >> c;
    }

    for (int age : start_ages)
        cnt += ages[age] * nr_of_children[age];

    cout << cnt << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}

void count(int age , map<int, size_t> &ages, map<int, size_t> &nr_of_children)
{
    int children = age + 1 <= DAYS ? 1 + (DAYS - age - 1) / 7 : 0;
    nr_of_children[age] = children;
    for (int j = 1; j <= children; ++j)
    {
        int a = age + 2 + j * 7;
        ++ages[a];
        if (ages[a] == 1)
            count(a, ages ,nr_of_children);
        nr_of_children[age] += nr_of_children[a];
    }
}