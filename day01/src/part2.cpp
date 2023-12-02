#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_2.txt");
    string line;
    int sum = 0;
    std::map<std::string, int> numberMap = {
        {"zero", 0},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}};
        int linecount = 0;
    while (getline(file, line))
    {
        linecount++;
        int res = 0;
        string tampon = "";
        string lineCopy = line;
        bool found = false;
        for (int i = 0; i < lineCopy.length(); i++)
        {
            if (found)
            {
                break;
            }
            if (isdigit(lineCopy[i]))
            {
                tampon = "";
                res += 10 * static_cast<int>(lineCopy[i] - '0');
                found = true;
                break;
            }
            else
            {
                tampon += lineCopy[i];
                for (auto &pair : numberMap)
                {
                    size_t pos = tampon.find(pair.first);
                    if (pos != std::string::npos)
                    {
                        res += 10 * pair.second;
                        found = true;
                        break;
                    }
                }
            }
        }
        tampon = "";
        found = false;
        for (int i = line.length()-1; i >=0; i--)
        {
            if (found)
            {
                break;
            }
            if (isdigit(line[i]))
            {
                tampon = "";
                res += static_cast<int>(line[i] - '0');
                found = true;
                break;
            }
            else
            {
                tampon = lineCopy[i] + tampon;
                for (auto &pair : numberMap)
                {
                    size_t pos = tampon.find(pair.first);
                    if (pos != std::string::npos)
                    {
                        res += pair.second;
                        found = true;
                        break;
                    }
                }
            }
        }
        sum += res;
    }
    cout << "Sum: " << sum << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}