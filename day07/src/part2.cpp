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

char getMaxdiff4(map<char, int> &m)
{
    char result = 'J';
    int maxdiff = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        if (it->second >= maxdiff && it->second < 5 && it->second != 0)
        {
            maxdiff = it->second;
            result = it->first;
        }
    }
    return result;
}
string computeJokers(string hand)
{
    if(hand=="JJJJJ")
    {
        return "JJJJJ";
    }
    string result;
    string handstr = hand;
    int occurence = count(handstr.begin(), handstr.end(), 'J');
    if (occurence == 0)
    {
        result = hand;
    }
    else
    {
        map<char, int> m;
        for (int i = 2; i < 10; i++)
        {
            m['0' + i] = 0;
        }
        m['J'] = 0;
        m['T'] = 0;
        m['J'] = 0;
        m['Q'] = 0;
        m['K'] = 0;
        m['A'] = 0;
        vector<char> to_replace;
        for (int i = 0; i < handstr.size(); i++)
        {
            if (handstr[i] != 'J')
            {
                m[handstr[i]] += 1;
            }
        }
            while (occurence > 0 && m[getMaxdiff4(m)] < 5)
            {
                if (getMaxdiff4(m) == getMaxdiff4(m))
                {
                    to_replace.push_back(getMaxdiff4(m));
                    m[getMaxdiff4(m)] += 1;
                    occurence--;
                }
            }
            reverse(to_replace.begin(), to_replace.end());
        for (int i = 0; i < handstr.size(); i++)
        {
            if (handstr[i] == 'J')
            {
                handstr[i] = to_replace.back();
                to_replace.pop_back();
            }
        }
        result = handstr;
    }
    return result;
}
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
    // insert elements into map
    for (int i = 2; i < 10; i++)
    {
        m['0' + i] = i;
    }
    m['J'] = 1;
    m['T'] = 10;
    m['Q'] = 12;
    m['K'] = 13;
    m['A'] = 14;
    for (int i = 0; i < m1.size(); i++)
    {
        if (m[m1[i]] > m[m2[i]])
        {
            return true;
        }
        else if (m[m1[i]] < m[m2[i]])
        {
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
        pair<string, int> hand1 = analyseHand(computeJokers(line_split[0]));
        pair<string, int> hand2 = analyseHand(line_split[0]);
        hand1.first = hand2.first;
        bids.push_back(line_split[1]);
        hand_results.push_back(hand1);
        ranking.push_back(0);
    }
    int placed = 0;
    while (placed < hand_results.size())
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
        vector<pair<string, int>> winners;
        for (int i = 0; i < hand_results.size(); i++)
        {
            if (hand_results[i].second == winner && ranking[i] == 0)
            {
                winner_count++;
                pair<string, int> winnerp;
                winnerp.first = hand_results[i].first;
                winnerp.second = i;
                winners.push_back(winnerp);
            }
        }
        sort(winners.begin(), winners.end(), [](const pair<string, int> &left, const pair<string, int> &right)
             { return compareEquals(left.first, right.first); });
        for (int i = 0; i < winners.size(); i++)
        {
            ranking[winners[i].second] = placed + i + 1;
        }
        placed += winners.size();
    }
    int result = 0;
    int size = ranking.size() + 1;
    for (int i = 0; i < ranking.size(); i++)
    {
        //cout << ranking[i] <<" " << hand_results[i].first << " : " << hand_results[i].second << endl;
        result += (size - ranking[i]) * stoi(bids[i]);
    }
    cout << "Result: " << result << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time elapsed: " << duration.count() << " µs" << endl;
    return 0;
}