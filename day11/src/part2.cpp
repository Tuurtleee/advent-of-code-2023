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

vector<pair<long int,long int>> expandUniverse(vector<pair<long int,long int>> map,long int& line_count, long int& col_count_max){
    vector<pair<long int,long int>> new_map;
    // first expanding on lines
    for(long int i=line_count-1; i>=0;i--){
        bool found = false;
        for(pair<long int,long int> p : map){
            if(p.first == i){
                found = true;
                break;
            }
        }
        if(!found){
            line_count+=999999;
            for(pair<long int,long int>& p : map){
                if(p.first >i){
                    p.first+=999999;
                }
            }
        }
    }
    //then expanding on columns
    for(long int i=col_count_max-1; i>=0;i--){
        bool found = false;
        for(pair<long int,long int> p : map){
            if(p.second == i){
                found = true;
                break;
            }
        }
        if(!found){
            col_count_max+=999999;
            for(pair<long int,long int>& p : map){
                if(p.second >i){
                    p.second+=999999;
                }
            }
        }
    }
    new_map = map;
    return new_map;

}

int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    vector<pair<long int,long int>> map;
    long int line_count = 0;
    long int col_count_max = 0;
    while (getline(file, line)) {
        vector<long int> row;
        long int col_count = 0;
        for (char c : line) {
            if (c == '#') {
                map.push_back(make_pair(line_count, col_count));
            }
            col_count++;
        }
        line_count++;
        col_count_max = col_count;
    }
    map = expandUniverse(map, line_count, col_count_max);

    long int result = 0;
    for(pair<long int,long int> p : map){
        for(pair<long int,long int> p2 : map){
            if(p.first == p2.first && p.second == p2.second){
                continue;
            }else{
                result+= abs(p.first-p2.first) + abs(p.second-p2.second);
            }
        }
    }
    cout<< "Result: " << result/2 << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}