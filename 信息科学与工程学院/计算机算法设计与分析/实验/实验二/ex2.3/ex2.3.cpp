#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Solution {
private:
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output.txt";
	
	int n; // n lines
	vector<vector<int>> input;
	
	/**
	 * 递归
	 **/
	int dfs(int row, int col) {
		if (row >= n) {
			return 0;
		}
		if (col > row) {
			return 0;
		}
		if (col < 0) {
			return 0;
		}
		
		else {
			return input[row][col] + max(dfs(row + 1, col), dfs(row + 1, col + 1));
		}
	}
	
	int getMaxNode(int row, int col, vector<vector<int>>& triangle) {
		if (row < 0 || row >= n || col < 0 || col >= n) {
			return 0;
		}
		if (col > row) {
			return 0;
		}
		if (row == n - 1) {
			return triangle[row][col];
		}
		else {
			return triangle[row][col] + max(triangle[row + 1][col], triangle[row + 1][col + 1]);
		}
	}
	
public:
	Solution() {
		ifstream inputFile(INPUT_FILE);
		
		if (!inputFile.is_open()) {
			cout << "Failed to open the file." << endl;
		}
		inputFile >> n;
		cout << "Get n successfully: " << n << endl;
		
		
		for (int i = 1; i <= n; i ++ ) {
			vector<int> line(i);
			for (int j = 0; j < i; j ++ ) {
				inputFile >> line[j];
			}
			input.emplace_back(line);
		}
		
		cout << "Get data successfully: " << endl;
		
		for (vector<vector<int>>::iterator it = input.begin(); it != input.end(); it ++ ) {
			for (vector<int>::iterator p = (*it).begin(); p != (*it).end(); p ++ ) {
				cout << *p << " ";
			}
			cout << endl;
		}
		
	}
	
	int getMaxSum_dfs() {
		return dfs(0, 0);
	}
	
	// down to up 
	// 自下到上
	int getMaxSum_dp_dtu() {
		vector<vector<int>> triangle = input; // protect the initialized data
		
		if (n == 1) {
			return input[0][0];
		}
		if (n < 1) {
			return 0;
		}
		
		for (int i = n - 2; i >= 0; i -- ) {
			for (int j = 0; j <= i; j ++ ) {
//				cout << "i, j, node " << i << " " << j << " "<< getMaxNode(i, j, triangle) << endl;
				triangle[i][j] = getMaxNode(i, j, triangle);
			}
		}
		return triangle[0][0];
	}
	
	// up to down
	int getMaxSum_dp_utd() {
		vector<vector<int>> triangle = input;
		
		for (int i = 1; i < n; i ++ ) {
			for (int j = 0; j <= i; j ++ ) {
				// 当前路径的最小值
				if (j == 0) {
					triangle[i][j] += triangle[i - 1][j];
				}
				else if (j == i) {
					triangle[i][j] += triangle[i - 1][j - 1];
				}
				else {
					triangle[i][j] += max(triangle[i - 1][j - 1], triangle[i - 1][j]);
				}
			}
		}
		
		int minSum = triangle[n - 1][0];
		
		for (const int & sum : triangle[n - 1]) {
			if (minSum < sum) {
				minSum = sum;
			}
		}
		
		return minSum;
	}
	
	void output() {
		int n(getMaxSum_dp_dtu());
		cout << "Answer is : " << n << endl;
		ofstream outputFile(OUTPUT_FILE);
		if (!outputFile.is_open()) {
			cout << "Failed to open the file." << endl;
		}
		
		outputFile << n;
		cout << "Write the data into the file." << endl;
		outputFile.close();
	}
};

int main() {
	Solution solution;
//	cout << solution.getMaxSum_dfs() << endl;
//	cout << solution.getMaxSum_dp_dtu() << endl;
//	cout << solution.getMaxSum_dp_utd() << endl;
	solution.output();
	
	return 0;
}
