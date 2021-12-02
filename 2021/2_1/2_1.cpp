#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int horizontal = 0, depth = 0, aim = 0;
    string direction;
    int val;

    while (in >> direction, in >> val)
    {
        if (direction == "forward")
        {
            horizontal += val;
            depth += aim * val;
        }
        if (direction == "up")
            aim -= val;
        if (direction == "down")
            aim += val;
    }
    cout << horizontal * depth << endl;
}