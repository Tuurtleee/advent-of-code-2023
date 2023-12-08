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


int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input/input_2.txt");
    string line;

    long int time = 0;
    long int record=0;

    getline(file, line);
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    regex reg("\\d+");
    sregex_iterator currentMatches(line.begin(), line.end(), reg);
    sregex_iterator lastMatches;
    while (currentMatches != lastMatches) {
        smatch match = *currentMatches;
        time = stol(match.str());
        currentMatches++;
    }
    getline(file, line);
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    sregex_iterator currentMatches2(line.begin(), line.end(), reg);
    while (currentMatches2 != lastMatches) {
        smatch match = *currentMatches2;
        record = stol(match.str());
        currentMatches2++;
    }
    int res = 0;
    for(int i=0;i<time/2+1;i++){
        if(record<(time-i)*i){
            if(i==time/2 && time%2==0){
                res += 1;
            }
            else{
                res += 2;
            }
        }
    }
    cout << "Result: " << res << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}