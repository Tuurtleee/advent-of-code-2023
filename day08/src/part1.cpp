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
int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    unordered_map<string,pair<string,string>> instructions;

    string geo="";
    while (getline(file, line)) {
        if(geo==""){
            geo=line;
        }else{
            if(line!=""){
                string key = line.substr(0,3);
                string value = line.substr(7,3);
                string value2 = line.substr(12,3);
                instructions[key]=make_pair(value,value2);
            }
        }
    }

    string current_state="AAA";
    int result = 0;
    int geoindex=0;
    while(current_state!="ZZZ"){
        result++;
        if(geoindex == geo.length()){
            geoindex=0;
        }
        current_state = getNextNode(&instructions,current_state,geo[geoindex]);
        geoindex++;
    }
    cout<<"Result: " << result << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}