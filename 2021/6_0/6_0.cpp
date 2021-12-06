#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int n;
    char c;

    vector<int> fish;
    while (in >> n)
    {
        fish.push_back(n);
        in >> c;
    }

    for (int i = 0; i < 80; ++i)
    {
        size_t sz = fish.size();
        for (size_t j = 0; j < sz; ++j)
        {
            if (fish[j] == 0)
            {
                fish[j] = 6;
                fish.push_back(8);
            }
            else --fish[j];
        }
    }
    cout << fish.size() << endl;
}