#include <iostream>
#include <fstream>
#include <chrono>
#include <stack>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string line;
    string open = "([{<";
    int result = 0;

    while (in >> line)
    {
        stack<char> brackets;
        for (char c : line)
        {
            if (open.find(c) != string::npos)
            {
                brackets.push(c);
                continue;
            }

            bool corrupt = false;
            switch (c)
            {
                case '>':
                    if (brackets.top() != '<')
                    {
                        result += 25137;
                        corrupt = true;
                    }
                    break;
                case ')':
                    if (brackets.top() != '(')
                    {
                        result += 3;
                        corrupt = true;
                    }
                    break;
                case ']':
                    if (brackets.top() != '[')
                    {
                        result += 57;
                        corrupt = true;
                    }
                    break;
                case '}':
                    if (brackets.top() != '{')
                    {
                        result += 1197;
                        corrupt = true;
                    }
                    break;      
            }
            if (corrupt) break;
            else brackets.pop();
        }
    }

    cout << result << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}