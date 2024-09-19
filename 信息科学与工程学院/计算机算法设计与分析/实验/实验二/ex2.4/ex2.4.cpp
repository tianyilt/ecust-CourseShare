#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output.txt";
	const int MAX_VALUE = 1e5;
	
	int n; // n yachts
	vector<vector<int>> data;
public:
	void input() {
		ifstream inputFile(INPUT_FILE);
		if (!inputFile.is_open()) {
			cout << "Failed to open input file." << endl;
		}
		inputFile >> n;
		
		cout << "Data got successfully: " << endl;
		cout << "n: " << n << endl;		
		// 0 1
		for (int i = 0; i < n - 1; i ++ ) {
			vector<int> temp; // i ~ n - 1
			for (int j = 0; j < n - 1 - i; j ++ ) {
				int a;
				inputFile >> a;
				temp.emplace_back(a);
			}
			data.emplace_back(temp);
		}
		
		for (vector<vector<int>>::iterator p = data.begin(); p != data.end(); p ++ ) {
			for (vector<int>::iterator q = (*p).begin(); q != (*p).end(); q ++ ) {
				cout << (*q) << " ";
			}
			cout << endl;
 		}
 		
 		inputFile.close();
 		if (inputFile.is_open()) {
 			cout << "Failed to close input file." << endl;
 		}
	}
	
	int getMinMoney() {
		if (n <= 1) {
			return data[0][0];
		}
		
		int res(0);
		
		for (int i = n - 2; i >= 0; i -- ) {
			int size = data[i].size();
			for (int j = 1; j < size; j ++ ) {
				for (int k = 0; k < j; k ++ )
					data[i][j] = min(data[i][j], data[i][k] + data[i + k + 1][j - k - 1]);
			}
		}
		
		/*
		cout << "test: " << endl;
		for (int i = 0; i < n; i ++ ) {
			for (int j = 0; j < data[i].size(); j ++ ) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
		*/
	
		return data[0][n - 2];
	}
	
	void output(int ans) {
		cout << "Get ans successfully: " << ans << endl;
		ofstream outputFile(OUTPUT_FILE);
		if (!outputFile.is_open()) {
			cout << "Failed to open file." << endl;
		}
		
		outputFile << ans << endl;
		
		cout << "Write the data into file." << endl;
		
		outputFile.close();
	}
};

int main() {
	Solution solution;
	solution.input();
	int ans = solution.getMinMoney();
	solution.output(ans);
	
	return 0;
}
