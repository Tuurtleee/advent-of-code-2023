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

pair<string, int> analyseHand(string hand)
{
    int result = 0;
    vector<char> hand_chars;
    for (int i = 0; i < hand.size(); i++)
    {
        hand_chars.push_back(hand[i]);
    }
    vector<int> hands_occurences;
    for (int i = 0; i < hand_chars.size(); i++)
    {
        int occurence = count(hand_chars.begin(), hand_chars.end(), hand_chars[i]);
        hands_occurences.push_back(occurence);
    }
    int max_occurence = *max_element(hands_occurences.begin(), hands_occurences.end());
    if (max_occurence == 3)
    { // we need to check if the other 2 cards are a pair
        bool found = false;
        for (int i = 0; i < hands_occurences.size(); i++)
        {
            if (hands_occurences[i] == 2)
            {
                result = 4; // full house
                found = true;
                break;
            }
        }
        if (!found)
        {
            result = 3; // three of a kind
        }
    }
    if (max_occurence == 2)
    {
        int nbpairs = count(hands_occurences.begin(), hands_occurences.end(), 2);
        if (nbpairs == 2)
        {
            result = 1; // one pairs
        }
        else
        {
            result = 2; // two pair
        }
    }
    if (max_occurence == 1)
    {
        result = 0; // high card
    }
    if (max_occurence == 4 || max_occurence == 5)
    {
        result = max_occurence + 1; // four/five of a kind
    }
    return make_pair(hand, result);
}
bool compareEquals(string m1, string m2)
{
    map<char, int> m;
    //insert elements into map
    for(int i=2;i<10;i++)
    {
        m['0'+i] = i;
    }
    m['T'] = 10;
    m['J'] = 11;
    m['Q'] = 12;
    m['K'] = 13;
    m['A'] = 14;
    for(int i=0;i<m1.size();i++){
        if(m[m1[i]] > m[m2[i]]){
            return true;
        }else if(m[m1[i]] < m[m2[i]]){
            return false;
        }
    }
    return true;
}

int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    vector<pair<string, int>> hand_results;
    vector<int> ranking;
    vector<string> bids;
    while (getline(file, line))
    {
        // split line at " "
        vector<string> line_split;
        stringstream ss(line);
        string word;
        while (getline(ss, word, ' '))
        {
            line_split.push_back(word);
        }
        pair<string, int> hand1 = analyseHand(line_split[0]);
        bids.push_back(line_split[1]);
        hand_results.push_back(hand1);
        ranking.push_back(0);
    }
    int placed = 0;
    while(placed < hand_results.size())
    {
        int winner = -1;
        int winner_count = 0;
        for (int i = 0; i < hand_results.size(); i++)
        {
            if (hand_results[i].second > winner && ranking[i] == 0)
            {
                winner = hand_results[i].second;
            }
        }
        vector<pair<string,int>> winners;
        for (int i = 0; i < hand_results.size(); i++)
        {
            if (hand_results[i].second == winner && ranking[i] == 0)
            {
                winner_count++;
                pair<string,int> winnerp;
                winnerp.first = hand_results[i].first;
                winnerp.second = i;
                winners.push_back(winnerp);
            }
        }
        sort(winners.begin(), winners.end(), [](const pair<string,int> &left, const pair<string,int> &right) {
            return compareEquals(left.first, right.first);
        });
        for(int i=0;i<winners.size();i++){
            ranking[winners[i].second] = placed + i + 1;
        }
        placed += winners.size();
    }
    int result = 0;
    int size = ranking.size() +1;
    for(int i=0;i<ranking.size();i++){
        result += (size - ranking[i]) * stoi(bids[i]);
    }
    cout << "Result: " << result << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}