#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {

    int num;
    int length; 
    int width;
    cin >> num;
    cin >> length >> width; 
    bool right; 
    vector<int> trees; //given distances (initial)
    trees.resize(num, 0);
    vector<double> spots; //if a spot is open [indices: 0 .... num] 
    spots.resize(num, -1);
    double answer;
    double min; 
    int index; //where to store min euc in spots vector
    int heightTemp = 0; 
    int widthTemp = 0;
    double euc = 0.0;
    vector<int> treesDup;  
    treesDup.resize(num, 0);


    for (int i = 0; i < num; i++) {
        cin >> trees[i];
    }


    std::sort(trees.begin(), trees.end());

    //cout << "hello" << endl;

    int spacing = length / (num/2 - 1);
    //cout << "spacing " << spacing << endl;
    int treesPerSide = num/2;

    int count = 0;

    for (int o = 0; o < trees.size(); o++) {
    	treesDup[o] = trees[o]%spacing; 
    }

    treesDup = trees;

    std::sort(treesDup.begin(), treesDup.end());

    //cout << "hello1" << endl;

    for (int j = 0; j < trees.size(); j++) {
        index = -1; 
        min = 0.0; 
        count = 0;

        //cout << "hello2" << endl;
        for (int k = 0; k < spots.size(); k++) {
            heightTemp = 0;
            widthTemp = 0;
            
            if (spots[k] == -1)  { //spot is empty
                count++;
                //cout << "current min is " << min << endl;
                right = (k - treesPerSide >= 0);
                //cout << k << " right is " << right << endl;
                heightTemp = trees[j] - (k - treesPerSide*((int)right))*(spacing);
                //cout << trees[j] << " - " << k << " - " << treesPerSide*(int)(right) << " * " << spacing;
                //cout << "height is " << abs(heightTemp) << endl;
                widthTemp = width*((int)right);
                //cout << "width is " << widthTemp << endl;
                euc = sqrt(pow(heightTemp, 2) + pow(widthTemp, 2));
                //cout << "euc " << euc << endl;

                //cout << "hello3" << endl;
                if (count == 1) {
                    min = euc;
                    //cout << "min is now " << min << endl;
                    index = k;
                }
                else if (min > euc) {
                    //cout << "min is " << min << " and is greater than " << euc << endl;
                    min = euc; 
                    index = k;
                }
            }
        }

        spots[index] = min;
        //cout << "setting index " << index << " to " << min << endl;
        
    }

    for (int l = 0; l < spots.size(); l++) {
        answer = answer + spots[l];
    }
    cout.precision(11);
    cout << answer << endl;
    return 0;



}