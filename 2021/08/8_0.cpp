#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string digit;
    int count = 0;

    while (!in.eof())
    {
        for (int i = 0; i < 11; ++i)
            in >> digit;

        for (int i = 0; i < 4; ++i)
        {
            in >> digit;
            switch (digit.size())
            {
                case 2:
                case 3:
                case 4:
                case 7:
                    ++count;
            }
        }
    }

    cout << count << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";   
}