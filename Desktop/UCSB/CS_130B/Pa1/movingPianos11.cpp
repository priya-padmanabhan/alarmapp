#include <iostream>
#include <vector>
#include <array>
#include <algorithm>


using namespace std; 

bool compare(const pair<int, int>&i, const pair<int, int>&j) {
    return i.second < j.second;
}

int main() {

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
    bool possibleWeekend = false;
    vector<int> counts(100);
    int range1 = 0;
    vector<int> tracker(100);
    bool seven = false;
    bool six = false;
    int sixInt;
    int sevenInt;


    for (int i = 0; i < numCases; i++) {
       // cout << "starting case " << i + 1 << endl;
        cin >> pianoNum >> tunNum; 


        days.clear(); 
        range.clear(); 

        for (int j = 0; j < pianoNum; j++) {
            cin >> startNum >> endNum;
            days.push_back(make_pair(j+1, endNum-startNum + 1));
            range.push_back(make_pair(startNum, endNum));
        }

        sort(days.begin(), days.end(), compare);

      // cout << "list for this test number sorted " << endl;

        for (int k = 0; k < days.size(); k++) {
        //  cout << days.at(k).first << " " << days.at(k).second << endl;
        }

        if (tunNum == 1) {
            serious = true;
            //answer.push_back("serious trouble");
            continue;
        }
        else {
            numPianoInDay = tunNum / 2;
        }


      //  cout << "max rate per day " << numPianoInDay << endl;
       // cout << "here" << endl;

        numDaysNeeded = pianoNum/numPianoInDay;
      //  cout << "min days needed to move all pianos by tuners " << numDaysNeeded << endl;

       


       for (int l = 0; l < range.size(); l++) {
         //   cout << "NEXT PIANO" << endl;
            for (int g = 0; g < days.size(); g++) {
                int l = days[g].first - 1;
             //   cout << "l is " << l << endl;
                for (int m = range[l].first; m < range[l].second + 1; m++) {
                 //   cout << "m is " << m << endl;
                  //  cout << "last element that should be looped is " << range[l].second << endl;
                    if (tracker[m] == numPianoInDay) {
                     //   cout << "full so need to skip " << endl;
                        if (g == range[m].second) {
                            serious = true;
                        }
                        continue;
                    }
                    if (tracker[m] == tracker.empty()  || tracker[m] < numPianoInDay){
                        tracker[m]++;
                        if (possibleWeekend == true) {
                         //   cout << "changing possWeek back to false" << endl;
                            possibleWeekend = false;
                            if (six == true) {
                                tracker[sixInt]--;
                            //    cout << "reduced sixInt to " << tracker[sixInt] << endl;
                                six = false;
                            }
                            if (seven == true) {
                                tracker[sevenInt]--;
                             //   cout << "reduced sevenInt to " << tracker[sevenInt] << endl;
                                seven = false;
                            }
                        }
                        /*
                        if (m % 6 != 0 && m % 7 != 0) {
                            break;
                        }*/
                      //  cout << m << " now has " << tracker[m] << endl;

                        if (numPianoInDay == 1 && m % 6 != 0 && m % 7 != 0) {
                        //     cout << "here5" << endl;
                        //    cout << "not a weekend and max hit " << endl;
                            if (m == range[l].second - 1 && (range[l].first != range[l].second)) {
                                serious = true;
                            }
                        //    cout << "break10000000" << endl;
                            break;
                        }

                        /*
                        else if (numPianoInDay == 1 && (m % 6 == 0 || m % 7 == 0)) {
                             cout << "here3" << endl;
                            weekend = true;
                            cout << "break1" << endl;
                            break;
                        }*/
                        else if (m % 6 == 0 || m % 7 == 0) {
                         //   cout << "here1" << endl;
                            possibleWeekend = true;
                            if (m % 6 == 0) {
                                six = true;
                                sixInt = m;
                            }
                            else {
                                seven = true;
                                sevenInt = m;
                            }
                        }
                        else {
                       //     cout << "break2" << endl;
                            break;
                        }
                    }
                    else {
                      //  cout << "hello " << endl;
                        if (tracker[m] < numPianoInDay) {
                        //    cout << "max of " << numPianoInDay << " has not been hit " << endl;
                         //    cout << "here8" << endl;
                            if (possibleWeekend == true) {
                                possibleWeekend = false;
                            }
                            tracker[m] = tracker[m] + 1;
                       //     cout << tracker[m] - 1 << endl;
                        //    cout << "increased count to " << tracker[m] << " for day " << m << endl;
                             
                             if (possibleWeekend == false) {
                          //      cout << "break3" << endl;
                                break;
                             }
                        }
                        else {
                       //     cout << "max has been hit" << endl;
                       //     cout << m << endl;
                        //     cout << "here9" << endl;
                        //     cout << "break4" << endl;
                            break;
                        }
                    }
                   // cout << "inserting num " << 1 << " under the date " << m << endl;

                    //find the piano num in the vector of pair of days and once thats found check the second item in the pair 

                    /*
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
                if (possibleWeekend == true) {
                     //   cout << "busted" << endl;
                        weekend = true;
                    }
                else {
                    fine = true;
                }

            }
            
        }
                
        
        /*
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
                
                }

            }
            */

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