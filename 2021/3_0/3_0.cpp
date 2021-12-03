#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    ifstream in("input.txt");
    vector<int> values(12, 0);
    string number;

    while (in >> number)
    {
        for (int i = 0; i < number.size(); ++i)
            values[i] += number[i] == '1' ? 1 : -1;
    }
    int gamma = 0;

    for (int i = 0; i < values.size(); ++i)
        if (values[i] > 0)
            gamma += pow(2, 12 - i - 1);

    int epsilon = gamma ^ 4095;
    cout << gamma * epsilon << endl;
}