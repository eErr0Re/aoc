#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cmath>
using namespace std;

string add(const string &, const string &);
int explode(string &, size_t, size_t);
pair<size_t, unsigned long long> magnitude(const string &, size_t);
unsigned long long magnitude(const string &);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string p1, p2;
    in >> p1;

    while (in >> p2)
        p1 = add(p1, p2);

    cout << magnitude(p1) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

string add(const string &p1, const string &p2)
{
    string res = "[" + p1 + "," + p2 + "]";
    int brackets = 0;

    // Explode
    for (size_t i = 0, prev = string::npos; i < res.size(); ++i)
    {
        if (res[i] == '[')
            ++brackets;
        else if (res[i] == ']')
            --brackets;
        else if (res[i] != ',' && i != prev + 1)
            prev = i;

        if (brackets == 5)
        {
            i = explode(res, i, prev);
            --brackets;
            prev = i;
        }
    }

    // Split
    for (size_t i = 0; i < res.size(); ++i)
    {
        if (res[i] == '[')
            ++brackets;
        else if (res[i] == ']')
            --brackets;
        else if (res[i] != ',')
        {
            auto end = res.find_first_of("[],", i);
            int val = stoi(res.substr(i, end - i));
            if (val < 10)
                continue;

            res.replace(i, end - i, "[" + to_string(val / 2) + "," + to_string((int) ceil(val / 2.0)) + "]");
            ++brackets;

            // Explode
            if (brackets == 5)
            {
                auto prev_end = res.find_last_not_of("[],", i);

                if (prev_end == string::npos)
                    i = explode(res, i, prev_end);
                else
                {
                    auto prev_start = res.find_last_of("[],", prev_end) + 1;
                    i = explode(res, i, prev_start);

                    auto prev_end = res.find_first_of("[],", prev_start);
                    // cout << res[prev_end - 1] << endl;

                    if (stoi(res.substr(prev_start, prev_end - prev_start)) >= 10)
                    {
                        i = -1;
                        brackets = 1;
                    }
                }

                --brackets;
            }
        }
    }

    return res;
}

// Explodes the string, returns new index
int explode(string &s, size_t start, size_t prev)
{
    auto comma = s.find(',', start);

    // Add to prev number if it exists
    if (prev != string::npos)
    {
        int val = stoi(s.substr(start + 1, comma - start - 1));
        auto prev_end = s.find_first_of("[],", prev);
        int prev_val = stoi(s.substr(prev, prev_end - prev));
        string sum = to_string(val + prev_val);
        s.replace(prev, prev_end - prev, sum);
        start += (sum.size() - (prev_end - prev));
    }

    comma = s.find(',', start);
    auto end = s.find(']', comma);

    auto next = s.find_first_not_of("[],", end);
    // Add to next number if it exists
    if (next != string::npos)
    {
        int val = stoi(s.substr(comma + 1, end - (comma + 1)));
        auto next_end = s.find_first_of("[],", next);
        int next_val = stoi(s.substr(next, next_end - next));
        string sum = to_string(val + next_val);
        s.replace(next, next_end - next, sum);
    }

    s.replace(start, end - start + 1, "0");
    
    return start;
}

unsigned long long magnitude(const string &s)
{
    return magnitude(s, 0).second;
}

// pair.first - end index (one after ]); pair.second - value
pair<size_t, unsigned long long> magnitude(const string &s, size_t start)
{
    ++start;
    unsigned long long sum = 0;
    pair<size_t, unsigned long long> p;

    // Evaluate left
    if (s[start] == '[')
    {
        p = magnitude(s, start);
        sum += 3 * p.second;
        start = p.first + 1;
    }
    else
    {
        size_t end = s.find(',', start);
        unsigned long long val = stoi(s.substr(start, end - start));
        sum += 3 * val;
        start = end + 1;
    }

    // Evaluate right
    if (s[start] == '[')
    {
        p = magnitude(s, start);
        sum += 2 * p.second;
        start = p.first + 1;
    }
    else
    {
        size_t end = s.find(']', start);
        unsigned long long val = stoi(s.substr(start, end - start));
        sum += 2 * val;
        start = end + 1;
    }

    return {start, sum};
}