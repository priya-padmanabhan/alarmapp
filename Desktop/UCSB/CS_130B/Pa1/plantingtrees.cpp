// take the tree with most amount of time and plant it first 
// 4
// 2 3 4 3

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
/*
1. Sort list of days from biggest to smallest
2. Create a vector of ints 
3. For each number, start one index over and add one to count for that many number of indices
4. keep track of current max 


    0 1 2 3 4 5
4 - 1 1 1 1      curr max = 5
3 -   1 1 1      curr max = 5
3 -     1 1 1    curr max = 6
2 -       1 1    curr max = 6

7 days 


vector of counts and then 

*/
int main() {

	//sort cin numbers 
	int numDays; 
	int day; 
	cin >> numDays;

	vector<int> storeCounts(numDays*50); 
	vector<int> dayNum;
	int maxDay = 0; 


	for (int p = 0; p < numDays; p++) {
		cin >> day; 
		dayNum.push_back(day);
	}


	sort(dayNum.begin(), dayNum.end(), greater<int>());

	for (int o = 0; o < dayNum.size(); o++) {
		cout << dayNum[o] << " " << endl;
	}

	cout << dayNum.size() << endl;
	
	int startVal = 0;

	for (int y = 0; y < storeCounts.size(); y++) {
		storeCounts[y] = 0;
	}

	for (int k = 0; k < dayNum.size(); k++) {
	//for the number of days present 
		cout << "k is " << k << endl;
		cout << dayNum[k] << endl;
		cout << "end of next for loop is " << startVal + dayNum[k] << endl;
		if (maxDay < startVal + dayNum[k]) {
			maxDay = startVal + dayNum[k];
		}
		for (int i = startVal; i < startVal + dayNum[k]; i++) {
			storeCounts[i] = storeCounts[i] + 1;
			cout << storeCounts[i] << "is updated for i = " << i << endl; 
		}
		startVal = startVal + 1;
	}

	maxDay = maxDay + 2; 

	cout << maxDay << endl;
	return 0;

}

//sorting algorithm to sort numbers and put into vector 



