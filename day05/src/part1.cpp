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

void applyRange(vector<long int> &v, vector<long int> &range, vector<bool>&vstatus){
    for(int i=0;i<v.size();i++){
        if(v[i] >= range[1] && v[i] < (range[1]+range[2]) && vstatus[i]==false){
            v[i] = range[0] + (v[i] - range[1]);
            vstatus[i] = true;
        }
    }
}
int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    vector<long int> v;
    vector<bool> vstatus;
    bool hasSeeds = false;
    string currentType = "seed";
    int lineType = 0;
    while (getline(file, line)) {
        if (hasSeeds==false){
            regex reg("\\d+");
            sregex_iterator currentMatches(line.begin(), line.end(), reg);
            sregex_iterator lastMatches;
            while (currentMatches != lastMatches) {
                smatch match = *currentMatches;
                v.push_back(stol(match.str()));
                vstatus.push_back(false);
                currentMatches++;
            }
            hasSeeds = true;
        }
        if(line==""){
            lineType = 0;
            continue;
        }
        regex reg(currentType + "-to-(\\w+)");
        std::smatch match;

        if (regex_search(line, match, reg) && match.size() > 1) {
            currentType = match.str(1);
            lineType = 1;
            for(int i=0;i<vstatus.size();i++){
                vstatus[i] = false;
            }
            continue;
        }
        if(lineType==1){ // we're getting the numbers
            regex reg("\\d+");
            sregex_iterator currentMatches(line.begin(), line.end(), reg);
            sregex_iterator lastMatches;
            vector<long int> v2;
            while (currentMatches != lastMatches) {
                smatch match = *currentMatches;
                v2.push_back(stol(match.str()));
                currentMatches++;
            }
            applyRange(v, v2, vstatus);
            lineType = 1;
            continue;
        }
        if(currentType=="location"){
            break;
        }
    }
    int min = *min_element(v.begin(), v.end());
    cout << "Minimum: " << min << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}