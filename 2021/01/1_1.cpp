#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int a, b, c, d;
    in >> a >> b >> c;
    int count = 0;
    while (in >> d)
    {
        if (b + c + d > a + b + c)
            ++count;

        a = b;
        b = c;
        c = d;
    }
    cout << count << endl;
}