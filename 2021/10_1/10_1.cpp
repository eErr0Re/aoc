#include <iostream>
#include <fstream>
#include <chrono>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string line;
    string open = "([{<";
    vector<long long> scores;

    while (in >> line)
    {
        bool corrupt = false;
        stack<char> brackets;
        for (char c : line)
        {
            if (open.find(c) != string::npos)
            {
                brackets.push(c);
                continue;
            }

            switch (c)
            {
                case '>':
                    if (brackets.top() != '<')
                        corrupt = true;
                    break;
                case ')':
                    if (brackets.top() != '(')
                        corrupt = true;
                    break;
                case ']':
                    if (brackets.top() != '[')
                        corrupt = true;
                    break;
                case '}':
                    if (brackets.top() != '{')
                        corrupt = true;
                    break;      
            }
            if (corrupt) break;
            else brackets.pop();
        }
        if (corrupt) continue;
        
        long long score = 0;
        while (!brackets.empty())
        {
            score *= 5;
            switch (brackets.top())
            {
                case '(':
                    ++score;
                    break;
                case '[':
                    score += 2;
                    break;
                case '{':
                    score += 3;
                    break;
                case '<':
                    score += 4;
                    break;
            }
            brackets.pop();
        }
        scores.push_back(score);
    }

    sort(scores.begin(), scores.end());

    cout << scores[scores.size() / 2] << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}