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


long int getNbSeed(vector<long int> v){//debug function (to check if we still have all the seeds)
    long int res = 0;
    for(int i = 0; i < v.size(); i++){
        if(i%2 == 1){
            res += v[i];
        }
    }
    return res;

}
vector<long int> applyRange(vector<long int> *v, vector<long int> range, vector<bool> *vstatus)
{
    vector<long int> res;
    vector<bool> vstatus2;
    long int base = 0;
    for (int i = 0; i < v->size(); i++)
    {
        if (i % 2 == 0)
        {
            base = v->at(i);
        }
        else
        {
            if(vstatus->at(i/2) == true){
                res.push_back(base);
                res.push_back(v->at(i));
                vstatus2.push_back(true);
                continue;
            }
            if (range[1] >= base && range[1] <= (base + v->at(i) - 1))
            {
                if(range[1]!=base)
                {
                    res.push_back(base);
                    res.push_back(range[1] - base);
                    vstatus2.push_back(false);
                }

                    if (range[1] + range[2] < base + (v->at(i)))
                    {
                        //OK
                        res.push_back(range[0]);
                        res.push_back(range[2]);
                        vstatus2.push_back(true);

                        res.push_back(range[1] + range[2]);
                        res.push_back(base + (v->at(i)) - (range[1] + range[2]));
                        vstatus2.push_back(false);
                    }else{
                        //OK
                        res.push_back(range[0]);
                        res.push_back(v->at(i) - (range[1] - base));
                        vstatus2.push_back(true);
                    
                    }
            }
            else if (base >= range[1] && base <= (range[1] + range[2] - 1))
            {
                    if (range[1] + range[2] < base + (v->at(i)))
                    { //OK
                        res.push_back(range[0] + base - range[1]);
                        res.push_back(range[2] + range[1] - base);
                        vstatus2.push_back(true);           

                        res.push_back(range[1]+range[2]);
                        res.push_back(base + (v->at(i)) - (range[1] + range[2]));
                        vstatus2.push_back(false);             
                    }else{
                        //OK
                        res.push_back(range[0]+ base - range[1]);
                        res.push_back(v->at(i));
                        vstatus2.push_back(true);
                    }

            }
            else
            {
                    res.push_back(base);
                    res.push_back(v->at(i));
                    vstatus2.push_back(false);
            }
        }
    }
    *vstatus = vstatus2;
    return res;
}
int main()
{
    auto start = high_resolution_clock::now();
    ifstream file("input/input_2.txt");
    string line;
    vector<long int> v;
    vector<bool> vstatus;
    bool hasSeeds = false;
    string currentType = "seed";
    int lineType = 0;

    long int nbSeeds = 0;
    while (getline(file, line))
    {
        if (hasSeeds == false)
        {
            regex reg("\\d+");
            sregex_iterator currentMatches(line.begin(), line.end(), reg);
            sregex_iterator lastMatches;
            int count = 0;
            while (currentMatches != lastMatches)
            {
                smatch match = *currentMatches;
                long int cur = stol(match.str());
                v.push_back(cur);
                count++;
                if (count % 2 == 0)
                    vstatus.push_back(false);
                currentMatches++;
            }
            nbSeeds = getNbSeed(v);
            hasSeeds = true;
        }
        if (line == "")
        {
            lineType = 0;
            continue;
        }
        regex reg(currentType + "-to-(\\w+)");
        std::smatch match;

        if (regex_search(line, match, reg) && match.size() > 1)
        {
            currentType = match.str(1);
            lineType = 1;
            for (int i = 0; i < vstatus.size(); i++)
            {
                vstatus[i] = false;
            }
            continue;
        }
        if (lineType == 1)
        { // we're getting the numbers
            regex reg("\\d+");
            sregex_iterator currentMatches(line.begin(), line.end(), reg);
            sregex_iterator lastMatches;
            vector<long int> v2;
            while (currentMatches != lastMatches)
            {
                smatch match = *currentMatches;
                v2.push_back(stol(match.str()));
                currentMatches++;
            }
            v = applyRange(&v, v2, &vstatus);
            if(nbSeeds != getNbSeed(v)){
                cout << "Seeds integrity failed" << endl;
                break;
            }
            lineType = 1;
            continue;
        }
    }
    long int min = v[0];
    for (int i = 0; i < v.size(); i++)
    {
        if (i % 2 == 0)
        {
            if (v[i] < min )
            {
                min = v[i];
            }
        }
    }
    cout << "Minimum: " << min << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Temps d'exécution: " << duration.count() << " µs" << endl;
    return 0;
}