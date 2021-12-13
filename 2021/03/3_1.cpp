#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ifstream in("input.txt");
    vector<string> oxygen, co2;
    string number;

    while (in >> number)
    {
        oxygen.push_back(number);
        co2.push_back(number);
    }

    int length = oxygen[0].size();

    for (int i = 0; i < length && (oxygen.size() != 1 || co2.size() != 1); ++i)
    {
        vector<string> next;

        int crit = 0;
        for (int j = 0; j < oxygen.size(); ++j)
            crit += oxygen[j][i] == '0' ? -1 : 1;
        crit = crit >= 0 ? 1 : 0;

        for (int j = 0; j < oxygen.size() && oxygen.size() != 1; ++j)
            if (oxygen[j][i] - '0' == crit) next.push_back(oxygen[j]);

        oxygen = next;
        next.clear();

        crit = 0;
        for (int j = 0; j < co2.size(); ++j)
            crit += co2[j][i] == '0' ? -1 : 1;
        crit = crit >= 0 ? 0 : 1;

        for (int j = 0; j < co2.size() && co2.size() != 1; ++j)
            if (co2[j][i] - '0' == crit) next.push_back(co2[j]);

        co2 = next;
    }
    cout << stoull(oxygen[0], 0, 2) * stoull(co2[0], 0, 2) << endl;
}
