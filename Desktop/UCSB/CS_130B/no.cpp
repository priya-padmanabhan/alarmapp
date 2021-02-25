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
			for (int k = 150; k >= seats[j]; k--) { 
				seat2[k] = max(probability[j]/100.0 * seat2[k-seats[j]], seat2[k]);

				if (k >= 76 && k < 151) {
					maximum = max(maximum, seat2[k]);
				}	
			}
		}

		printf("%.2f", maximum *= 100);
		cout << endl;

	}
	return 0;
}
