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

int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_1.txt");
    string line;
    int result = 0;
    while (getline(file, line))
    {
        int points = 0;
        // split line at ":"
        string delimiter = ":";
        string cards = line.substr(line.find(delimiter) + 1, line.length());
        // split at "|
        delimiter = "|";
        string winning = cards.substr(0, cards.find(delimiter));
        string current = cards.substr(cards.find(delimiter) + 1, cards.length());

        vector<int> winning_cards;
        vector<int> current_cards;

        std::istringstream iss(winning);
        int number;
        while (iss >> number)
        {
            winning_cards.push_back(number);
        }

        std::istringstream iss2(current);
        while (iss2 >> number)
        {
            current_cards.push_back(number);
        }
        for (int i = 0; i < current.size(); i++)
        {
            if (std::find(winning_cards.begin(), winning_cards.end(), current_cards[i]) != winning_cards.end())
            {
                if (std::find(winning_cards.begin(), winning_cards.end(), current_cards[i]) != winning_cards.end())
                {
                    if (points == 0)
                    {
                        points = 1;
                    }
                    else
                    {
                        points *= 2;
                    }
                }
            }
        }
        result += points;
    }
    cout << "Result: " << result << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Temps d'exécution: " << duration.count() << " µs" << endl;
    return 0;
}