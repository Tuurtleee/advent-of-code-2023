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
    int sum = 0;
    while (getline(file, line)) {
        string val = "";
        for(int i=0;i<line.length();i++) {
            if (isdigit(line[i])) {
                val += line[i];
                break;
            }
        }
        for(int i=line.length()-1;i>=0;i--) {
            if (isdigit(line[i])) {
                val += line[i];
                break;
            }
        }
        int numval = stoi(val);
        sum += numval;
    }
    cout << sum << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Temps d'exécution: " << duration.count() << " µs" << endl;
    return 0;
}