#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <vector>
#include <regex>
#include <chrono>
#include <iterator>

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_2.txt");
    string line;
    regex e("\\d+");
    regex eg("(\\d+) green");
    regex eb("(\\d+) blue");
    regex er("(\\d+) red");
    int sum = 0;
    while (getline(file, line))
    {
        smatch m;
        regex_search(line, m, e);
        int red = 0;
        int blue = 0;
        int green = 0;
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), m, eg))//green
        {
            green = max(stoi(m[1]), green);
            searchStart = m.suffix().first;
        }

        searchStart = line.cbegin();
        while (regex_search(searchStart, line.cend(), m, eb))//blue
        {
            blue = max(stoi(m[1]), blue);
            searchStart = m.suffix().first;
        }

        searchStart = line.cbegin();
        while (regex_search(searchStart, line.cend(), m, er))//red
        {
            red = max(stoi(m[1]), red);
            searchStart = m.suffix().first;
        }
        sum += red * green * blue;
    }
    cout << "Sum: " << sum << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}