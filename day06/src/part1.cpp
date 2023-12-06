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
    ifstream file("input/input_1.txt");
    string line;

    getline(file, line);
    vector<int> times;
    regex reg("\\d+");
    sregex_iterator currentMatches(line.begin(), line.end(), reg);
    sregex_iterator lastMatches;
    while (currentMatches != lastMatches) {
        smatch match = *currentMatches;
        times.push_back(stoi(match.str()));
        currentMatches++;
    }
    vector<int> records;
    getline(file, line);
    sregex_iterator currentMatches2(line.begin(), line.end(), reg);
    while (currentMatches2 != lastMatches) {
        smatch match = *currentMatches2;
        records.push_back(stoi(match.str()));
        currentMatches2++;
    }
    int res=1;
    int cur=0;
    for(int i=0;i<times.size();i++){
        for(int j=0;j<times[i]/2+1;j++){
            if(records[i]<(times[i]-j)*j){
                if(j==times[i]/2 && times[i]%2==0){
                    cur += 1;
                }
                else{
                    cur += 2;
                }
            }
        }
        if(cur>0)
        res *= cur;
        cur = 0;
    }
    cout << "Result: " << res << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Temps d'exécution: " << duration.count() << " µs" << endl;
    return 0;
}