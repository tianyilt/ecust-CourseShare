#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
private:
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output1.txt";
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
	
	int solve(vector<vector<int>>& data, int n) {
		vector<int> dp = data[0];
		for(int i = 1; i < n - 1; i ++) {
			for(int j = 0; j < i; j ++)
				dp[i] = min(dp[i], dp[j] + data[j + 1][i - j - 1]);
			//for(int i = 0; i < n - 1; i ++) cout << dp[i] << ' ';
			//cout<< "\n";
		}
		return dp[n - 2];
	}
	
	int getAnswer() {
		return solve(data, n);
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

int main(){
	Solution solution;
	solution.input();
	int ans = solution.getAnswer();
	solution.output(ans);
	
	return 0;
}
