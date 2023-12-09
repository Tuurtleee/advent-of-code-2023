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

bool isConsistent(vector<int> &line){
    for(int i = 0; i < line.size(); i++){
        if(line[i] !=0){
            return false;
        }
    }
    return true;
}

int getNextValue(vector<int> &history){
    vector<vector<int>> devhist;
    devhist.push_back(history);
    while(!isConsistent(devhist[devhist.size()-1])){//descent
        vector<int> newline;
        vector<int> lastline = devhist[devhist.size()-1];
        for(int i=0;i<lastline.size()-1;i++){
            newline.push_back(lastline[i+1]-lastline[i]);
        }
        devhist.push_back(newline);
    }
    int rem = 0;
    for(int k=devhist.size()-1;k>=0;k--){
        vector<int> line = devhist[k];
        rem = line[0] - rem;
    }
    return rem;
}

int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    int result = 0;
    while (getline(file, line)) {
        vector<int> history;
        istringstream iss(line);
        int number;
        while (iss >> number) {
            history.push_back(number);
        }
        result += getNextValue(history);
    }
    cout << "Result: " << result << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}