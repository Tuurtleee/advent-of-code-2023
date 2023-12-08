#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;


long int ppcm(long int a, long int b)
{
    return a * b / gcd(a, b);
}
long int ppcm_vector(const std::vector<int> &numbers)
{
    long int result = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
    {
        result = ppcm(result, numbers[i]);
    }
    return result;
}
string getNextNode(unordered_map<string, pair<string, string>> *instructions, string current, char direction)
{
    if (direction == 'R')
    {
        return (*instructions)[current].second;
    }
    else
    {
        return (*instructions)[current].first;
    }
}
int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    unordered_map<string, pair<string, string>> instructions;

    string geo = "";
    vector<string> states;
    while (getline(file, line))
    {
        if (geo == "")
        {
            geo = line;
        }
        else
        {
            if (line != "")
            {
                string key = line.substr(0, 3);
                string value = line.substr(7, 3);
                string value2 = line.substr(12, 3);
                instructions[key] = make_pair(value, value2);
                if (key[2] == 'A')
                {
                    states.push_back(key);
                }
            }
        }
    }

    long int result = 0;
    vector<int> vals;
    for (int i = 0; i < states.size(); i++)
    {
        int geoindex = 0;
        int val = 0;
        string current_state = states[i];
        while (current_state[2] != 'Z')
        {
            val++;
            if (geoindex == geo.length())
            {
                geoindex = 0;
            }
            current_state = getNextNode(&instructions, current_state, geo[geoindex]);
            geoindex++;
        }
        vals.push_back(val);
    }
    result = ppcm_vector(vals);
    cout << "Result: " << result << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}