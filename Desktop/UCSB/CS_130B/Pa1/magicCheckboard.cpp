#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main() {
	vector<vector<int> > matrix(3); 
	cout << matrix.size() << endl;
	vector<int> innerMatrix(3);
	cout << innerMatrix.size() << endl;

	cout << "test" << endl;
	for (int i = 0; i < 4; i++) {
		matrix.push_back(innerMatrix);
	}


	matrix[0].push_back(1);
	matrix[0].push_back(2);
	matrix[0].push_back(3);
	matrix[0].push_back(0);

	matrix[1].push_back(0);
	matrix[1].push_back(0);
	matrix[1].push_back(5);
	matrix[1].push_back(6);

	matrix[2].push_back(0);
	matrix[2].push_back(4);
	matrix[2].push_back(7);
	matrix[2].push_back(8);


	matrix[3].push_back(7);
	matrix[3].push_back(0);
	matrix[3].push_back(0);
	matrix[3].push_back(10);

	/*
	string filename; 
	ifstream inputfile; 
	ofstream outfile("answer.txt");

	filename = argv[1];

	ifstream inputfile(filename);
	inputfile.open(filename);

	if (inputfile.good()){
		string sLine;
		string getline(inputfile, sLine);
		int row = sLine[0];
		int column = sLine[2];
		vector<vector<int>> matrix; 

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				matrix[i].push_back(getline())

}
		}

	}

	*/

	vector<int> diag1; 
	vector<int> diag2;
	int nextValPos; 

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] == 0) {
				cout << "THE VALUE IS " << matrix[i][j] << endl;
				if (j != 0) {
					cout << "not at first element and we are looking at " << i << " " << j << endl;
					matrix[i][j] = matrix[i][j - 1] + 1;
					cout << "value at " << i << " " << j << " " << "is " << matrix[i][j] << endl;
				}
				else {
					cout << "here!!!!" << endl;
					matrix[i][j] = matrix[i][j + 1] - 1;
					cout << i << " " << j <<  " is currently " << matrix[i][j] << endl;
					nextValPos = 1;
					while (nextValPos >= 1) {
						if (matrix[i][j + nextValPos] == 0) {
							nextValPos++;
							cout << "nextValPos is now " << nextValPos << endl;
						} 
						else {
							while (nextValPos > 0) {
								matrix[i][j + nextValPos - 1] = matrix[i - 1][j + nextValPos - 1] + 1;
								if (matrix[i][j + nextValPos - 1] > matrix[i][j + nextValPos] - 1) {
									matrix[i][j + nextValPos - 1] = matrix[i][j + nextValPos] - 1;
								} 
								cout << "value at " << i << " " << j + nextValPos -1 << " " << "is " << matrix[i][j + nextValPos - 1] << endl;
								nextValPos--;
								cout << "nextValPos is now " << nextValPos << endl;
							}
						}
					}
					
				}
			}
		}
	}



	bool checkRow = false;
	bool checkCol = false;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] > matrix[i][j + 1]) {
				matrix[i][j] = matrix[i][j] - 1;
			}
		}
		cout << endl;
	}

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}

/*
int checkNumType(int value) {
	if (value % 2 == 0) {
		return 0; 
	}
	else {
		return 1;
	}
}

*/