#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <vector>
#include <chrono>
#include <regex>
using namespace std;
using namespace std::chrono;

typedef pair<int, int> Position;
typedef vector<int> Neighbors;
map<Position, Neighbors> numberNeighbors;

void getNumbers(string &line_1,string &line,string &line_p1,int id){
    //checking last line
    vector<int> indexes;
        bool status = false;
        int index_in_line = 0;
        for (int i = 0; i < line_p1.size(); i++)
        {
            if (isdigit(line[i]) && !status)
            {
                indexes.push_back(i);
                status = true;
            }
            if (status && !isdigit(line[i]))
                status = false;
        }
        for (int i = 0; i < indexes.size(); i++)
        {
            int current_id = id;
            bool hasNeighbour = false;
            // checking char before
            if (indexes[i] > 0)
            {
                if (line[indexes[i]-1] == '*')
                {
                    hasNeighbour = true;
                    index_in_line = indexes[i]-1;
                }
            }
            // checking char after
            int k = indexes[i];
            while (isdigit(line[k]))
            {
                k++;
            }
            if (k < line.size())
            {
                if (line[k] == '*')
                {
                    hasNeighbour = true;
                    index_in_line = k;
                }
            }
            // checking all chars in next line between indexes[i]-1 and k+1
            for (int j = indexes[i] - 1; j < k + 1; j++)
            {
                if (j < 0 || j > line.size() - 1)
                    continue;
                if (line_p1[j] == '*')
                {
                    hasNeighbour = true;
                    index_in_line = j;
                    current_id = current_id+1;
                }
            }
            if (line_1 != "")
            {
                for (int j = indexes[i] - 1; j < k + 1; j++)
                {
                    if (j < 0 || j > line.size() - 1)
                        continue;
                    if (line_1[j] == '*')
                    {
                        hasNeighbour = true;
                        index_in_line = j;
                        current_id = current_id-1;
                    }
                }
            }
            if (hasNeighbour)
            {
                // getting full number
                int l = indexes[i];
                while (l < line.size() && isdigit(line[l]))
                {
                    l++;
                }
                string number = line.substr(indexes[i], l - indexes[i]);
                if (!number.empty() && std::all_of(number.begin(), number.end(), ::isdigit))
                {
                    int n = stoi(number);
                    Position p = make_pair(current_id, index_in_line);
                    numberNeighbors[p].push_back(n);
                }
            }
        }
}

int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_2.txt");
    string line;
    string line_1 = "";
    string line_p1 = "";
    getline(file, line);
    int sum = 0;
    int id = 0;
    while (getline(file, line_p1))
    {
        getNumbers(line_1,line,line_p1,id);
        line_1.resize(line_p1.size());
        line.resize(line_p1.size());
        copy(line.begin(), line.end(), line_1.begin());
        copy(line_p1.begin(), line_p1.end(), line.begin());
        id++;
    }
    getNumbers(line_1,line,line_p1,id);
    for (auto const &x : numberNeighbors)
    {
        if (x.second.size() == 2)
        {
            sum += x.second[0] * x.second[1];
        }
    }
    cout << "Sum: " << sum << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}