#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <vector>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

string exploreFromDir(vector<vector<char>> &map1, int dir, int x, int y, string chain)
{
    map<char, pair<int, int>> dirMap;
    dirMap['|'] = make_pair(1, 3);
    dirMap['-'] = make_pair(0, 2);
    dirMap['L'] = make_pair(0,1);
    dirMap['J'] = make_pair(1,2);
    dirMap['7'] = make_pair(2,3);
    dirMap['F'] = make_pair(3,0);
    chain += map1[x][y];
    if (map1[x][y] == 'S')
    { // on a terminé le cycle
        return chain;
    }
    else if(map1[x][y] == '.')
    {
        return "";
    }
    else
    {
        vector<string> res;
        if (dirMap[map1[x][y]].first == dir)
        {
            if(dirMap[map1[x][y]].second == 0){
                if(y!=map1[0].size()-1){
                    res.push_back(exploreFromDir(map1, 2, x, y+1, chain));
                }
            }
            else if(dirMap[map1[x][y]].second == 1){
                if(x!=0){
                    res.push_back(exploreFromDir(map1, 3, x-1, y, chain));
                }
            }
            else if(dirMap[map1[x][y]].second == 2){
                if(y!=0){
                    res.push_back(exploreFromDir(map1, 0, x, y-1, chain));
                }
            }
            else if(dirMap[map1[x][y]].second == 3){
                if(x!=map1[0].size()-1){
                    res.push_back(exploreFromDir(map1, 1, x+1, y, chain));
                }
            }
        }else if((dirMap[map1[x][y]].second == dir)){
            if(dirMap[map1[x][y]].first == 0){
                if(y!=map1[0].size()-1){
                    res.push_back(exploreFromDir(map1, 2, x, y+1, chain));
                }
            }
            else if(dirMap[map1[x][y]].first == 1){
                if(x!=0){
                    res.push_back(exploreFromDir(map1, 3, x-1, y, chain));
                }
            }
            else if(dirMap[map1[x][y]].first == 2){
                if(y!=0){
                    res.push_back(exploreFromDir(map1, 0, x, y-1, chain));
                }
            }
            else if(dirMap[map1[x][y]].first == 3){
                if(x!=map1.size()-1){
                    res.push_back(exploreFromDir(map1,1, x+1, y, chain));
                }
            }
        }
        for(string s : res){
            if(s != ""){
                return s;
            }
        }
    }
    return "";
}
string getMainLoop(vector<vector<char>> &map, int x, int y)
{
    string chain = "S";
    if (x != 0)
    {
        string temp = exploreFromDir(map, 3, x - 1, y, chain);
        if(temp != ""){
            return temp;
        }
    }
    if (x != map.size() - 1)
    {
        string temp = exploreFromDir(map, 1, x + 1, y, chain);
        if(temp != ""){
            return temp;
        }
    }
    if (y != 0)
    {
        string temp = exploreFromDir(map, 0, x, y - 1, chain);
        if(temp != ""){
            return temp;
        }
    }
    if (y != map[0].size() - 1)
    {
        string temp = exploreFromDir(map, 2, x, y + 1, chain);
        if(temp != ""){
            return temp;
        }
    }
    return "";
}

int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    vector<vector<char>> map;
    int x = 0;
    int y = 0;
    int k = 0;
    while (getline(file, line))
    {
        vector<char> cur;
        int i = 0;
        for (char c : line)
        {
            cur.push_back(c);
            if (c == 'S')
            {
                x = k;
                y = i;
            }
            i++;
        }
        k++;
        map.push_back(cur);
    }
    string mainloop = getMainLoop(map, x, y);
    cout << "Result: "<< (mainloop.length()-1)/2 << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}