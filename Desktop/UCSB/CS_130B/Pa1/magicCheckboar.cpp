#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(char *argv[]) {
	vector<vector<int>> matrix; 
	for (int i = 0; i < matrix.length(); i++) {
		matrix.push_back(vector<int> innerMatrix);
	}

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

	array[int] diag1; 
	array[int] diag2;

	for (int i = 0; i < matrix.length(); i++) {
		for (int j = 0; j < matrix[i].length(); j++) {
			if (matrix[i][j] == 0) {
				if (j != 0) {
					matrix[i][j] = matrix[i][j - 1] - 1;
				}
				else {
					matrix[i][j] = matrix[i][j + 1] + 1;
				}
			}
		}
	}

	return;
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