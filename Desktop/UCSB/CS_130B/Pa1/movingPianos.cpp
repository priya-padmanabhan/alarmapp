#include <iostream>
#include <vector>
#include <array>
#include <algorithm>


using namespace std; 

bool compare(const pair<int, int>&i, const pair<int, int>&j) {
    return i.second < j.second;
}

int main() {

    /*

    6 pianos 11 tuners ---- 2 days
    1 1
    1 1
    1 1
    1 1
    1 1
    1 1


    */


    int numCases; 
    int pianoNum;
    int tunNum;
    int numDaysNeeded; 
    int numPianoInDay = 0; //keeps track of how many possible pianos can be moved in a day 
    int startNum; 
    int endNum;
    cin >> numCases;
    vector<pair<int, int> > days;
    vector<pair<int, int> > range;
    vector<string> answer;
    bool weekend = false;
    bool fine = false;
    bool serious = false;
    vector<int> counts(100);
    int range1 = 0;

    for (int i = 0; i < numCases; i++) {
        cout << "starting case " << i + 1 << endl;
        cin >> pianoNum >> tunNum; 


        days.clear(); 
        range.clear(); 

        for (int j = 0; j < pianoNum; j++) {
            cin >> startNum >> endNum;
            days.push_back(make_pair(j+1, endNum-startNum + 1));
            range.push_back(make_pair(startNum, endNum));
        }

        sort(days.begin(), days.end(), compare);

       cout << "list for this test number sorted " << endl;

        for (int k = 0; k < days.size(); k++) {
          cout << days.at(k).first << " " << days.at(k).second << endl;
        }

        if (tunNum == 1) {
            serious = true;
            //answer.push_back("serious trouble");
            continue;
        }
        else {
            numPianoInDay = tunNum / 2;
        }
/*
        for (int w = 0; w < range.size(); w++) {
            for (int y = range[w].first; y < range[w].second + 1; y++) {
                counts[y] = 1;
            }
        }

        for (int u = 0; u < counts.size(); u++) {
            if (counts[u] == 1) {
                range1++;
            }
        }*/

       cout << "max rate per day " << numPianoInDay << endl;

        numDaysNeeded = pianoNum/numPianoInDay;
        cout << "min days needed to move all pianos by tuners " << numDaysNeeded << endl;
        int maxRange = days[pianoNum - 1].second;
       

        if (startNum == endNum) {
            cout << startNum << "==" << endNum << endl;
            if (startNum % 7 == 0 || endNum % 6 == 0) {
                if (answer.size() == i ){
                    cout << "size of answer array rn is " << answer.size() << endl;
                    weekend = true;
                    cout << "setting weekend to true" << endl;
                    answer.push_back("weekend work");
                }
            }

            
           else {
                if (numDaysNeeded == 1) {
                    answer.push_back("fine");
                    fine = true;
                    cout << "setting fine to true" << endl;
                }
            }
            
        }


        if (numDaysNeeded > maxRange) {
            cout << "serious trouble" << endl;
            cout << "size of answer array rn is " << answer.size() << endl;
            //answer.push_back("serious trouble");

            serious = true;
            cout << "setting serious to true" << endl;
        }

        for (int l = 0; l < range.size(); l++) {
            cout << "here" << endl;
            for (int m = range[l].first; m < range[l].second + 1; m++) {
                if (numDaysNeeded == maxRange) {
                    if (m % 7 == 0 ||  m % 6 == 0) {
                        cout << "weekend work" << endl;
                        weekend = true;
                        cout << "setting weekend to true" << endl;
                    }
                }
                else {
                    if (answer.size() == i){
                        fine = true;
                        cout << "setting fine to true" << endl;
                    }
                }

                //tracker[m].push_back(l + 1);
                cout << "inserting piano num " << l + 1 << " under the date " << m << endl;
                /*
                //find the piano num in the vector of pair of days and once thats found check the second item in the pair 
                for (int n = 0; n < days.size(); n++) {
                    if (days[n].first == l + 1) {
                        if (days[n].second == 1 && (range[l].first %7 == 0 || range[l].first %6 == 0)) {
                            cout << "weekend work" << endl;
                        }
                        if (days[n].second == 2 && (range[l].first %6 == 0 && range[l].second %7== 0)) {
                            cout << "weekend work" << endl;
                        }
                    }
                }
                */
                }

            }

            if (serious == true) {
                answer.push_back("serious trouble");
            
            }
            else if (weekend == true) {
                answer.push_back("weekend work");
            
            }

            else if (fine == true) {
                answer.push_back("fine");
            
            }

            serious = false;
            weekend = false;
            fine = false;
        }
        



    for (int h = 0; h < answer.size(); h++) {
        cout << answer[h] << endl;
    }

    return 0;
}