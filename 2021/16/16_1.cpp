#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

string toBinary(const string &);
int evaluate(const string &, vector<unsigned long long> &values, int start = 0);

int main()
{
    auto start = chrono::steady_clock::now();

    ifstream in("input.txt");
    string transmission;
    in >> transmission;
    transmission = toBinary(transmission);

    vector<unsigned long long> val;
    evaluate(transmission, val);

    cout << val[0] << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

int evaluate(const string &transmission, vector<unsigned long long> &values, int start)
{
    int version = stoi(transmission.substr(start, 3), 0, 2);
    int type = stoi(transmission.substr(start + 3, 3), 0, 2);

    if (type == 4)
    {
        string val;
        for (int i = start + 6; i < transmission.size(); i += 5)
        {
            val += transmission.substr(i + 1, 4);
            if (transmission[i] == '0')
            {
                values.push_back(stoull(val, 0, 2));
                return i + 5;
            }
        }
    }

    int length_type = transmission[start + 6] == '1';
    vector<unsigned long long> val;
    int next;

    if (length_type)
    {
        int number = stoi(transmission.substr(start + 7, 11), 0, 2);
        next = start + 18;
        for (int i = 0; i < number; ++i)
            next = evaluate(transmission, val, next);
    }
    else
    {
        int number = stoi(transmission.substr(start + 7, 15), 0, 2);
        next = start + 22;
        while (next - start - 22 < number)
            next = evaluate(transmission, val, next);
    }

    switch (type)
    {
        case 0:
            values.push_back(accumulate(val.cbegin(), val.cend(), 0ull));
            break;
        case 1:
            values.push_back(accumulate(val.cbegin(), val.cend(), 1ull, multiplies<unsigned long long>()));
            break;
        case 2:
            values.push_back(*min_element(val.cbegin(), val.cend()));
            break;
        case 3:
            values.push_back(*max_element(val.cbegin(), val.cend()));
            break;
        case 5:
            values.push_back(val[0] > val[1]);
            break;
        case 6:
            values.push_back(val[0] < val[1]);
            break;
        case 7:
            values.push_back(val[0] == val[1]);
            break;
    }

    return next;
}

string toBinary(const string &hex)
{
    string res;
    res.reserve(hex.size() * 4);

    for (char c : hex)
    {
        switch (c)
        {
            case '0':
                res += "0000";
                break;
            case '1':
                res += "0001";
                break;
            case '2':
                res += "0010";
                break;
            case '3':
                res += "0011";
                break;
            case '4':
                res += "0100";
                break;
            case '5':
                res += "0101";
                break;
            case '6':
                res += "0110";
                break;
            case '7':
                res += "0111";
                break;
            case '8':
                res += "1000";
                break;
            case '9':
                res += "1001";
                break;
            case 'A':
                res += "1010";
                break;
            case 'B':
                res += "1011";
                break;
            case 'C':
                res += "1100";
                break;
            case 'D':
                res += "1101";
                break;
            case 'E':
                res += "1110";
                break;
            case 'F':
                res += "1111";
                break;
        }
    }
    return res;
}
