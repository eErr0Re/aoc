#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int horizontal = 0, depth = 0;
    string direction;
    int val;

    while (in >> direction, in >> val)
    {
        if (direction == "forward")
            horizontal += val;
        if (direction == "up")
            depth -= val;
        if (direction == "down")
            depth += val;
    }
    cout << horizontal * depth << endl;
}