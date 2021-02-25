#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int tests;
    int number; 
    cin >> tests;
    vector<int> probability;
    vector<int> seats;
    vector<double> seat2; 

    while (tests--) {
        cin >> number;
        int old = 0;
        double old2 = 0.0;
        double maximum = 0.0;
        probability.clear();
        seats.clear();
        seat2.clear();
        probability.resize(number, 0);
        seats.resize(number, 0);
        seat2.resize(151, 0);
        seat2[0] = 1.0; 

        for (int i = 0; i < number; i++) {
            cin >> seats[i] >> probability[i];
        }

        for (int j = 0; j < number; j++) { 
            for (int k = 150; k >= seats[j]; k--) { //150 to the number of seats won by each party 
                //old = seat2[k];
                seat2[k] = max(probability[j]/100.0 * seat2[k-seats[j]], seat2[k]);
                //cout << "the value in seat2[" << k << "] is max of " <<  probability[j]/100.0  << " times " << seat2[k-seats[j]] << " and " << old << " which is " << seat2[k] << endl;
                //cout << k << " value is " << seat2[k] << endl;

`
                if (k >= 76 && k < 151) {
                   // old2 = maximum;
                    maximum = max(maximum, seat2[k]);
                   // cout << "maximum between " << old2 << " and " << seat2[k] << " where k is " << k << " is " << maximum << endl;
                }   
            }
        }

        cout.precision(11);
        maximum *= 100;
        cout <<  fixed << maximum << endl;

    }
    return 0;
}