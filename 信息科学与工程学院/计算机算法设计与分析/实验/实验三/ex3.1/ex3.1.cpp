/**
 * 5-1 子集和问题
 **/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
private:
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output.txt";
	const static int INVALID = -1;
	
	vector<int> s;
	vector<bool> bestx; // 对于s中，选或者不选
	int n, c;
	int bestw; // 已选元素之和
	int finalSum; // 当前元素加上最后一个元素的总和
	
public:
	Solution() {
		n = INVALID;
		c = INVALID;
		s.clear();
		bestx.clear();
		bestw = 0;
		finalSum = 0;
		
		// 查看是否存在input.txt文件，不存在创建
		ifstream inputFile(INPUT_FILE);
		
		if (!inputFile.good()) {
			ofstream output(INPUT_FILE);
			cout << "input.txt不存在，正在创建" << endl;
			if (!output.is_open()) {
				cout << "创建失败";
				exit(0);
			}
			string content = 
				"5 10\n"
				"2 2 6 5 4\n";
			output << content;
			output.close();
		}
		
		inputFile.close();
	}
	
	~Solution() {
		s.clear();
		bestx.clear();
	}
	
	bool input() {
		ifstream inputFile(INPUT_FILE);
		
		if (!inputFile.is_open()) {
			cout << "Cannot open file input.txt" << endl;
		}
		
		inputFile >> n >> c;
		if (n == INVALID || c == INVALID) {
			cout << "Cannot get the value of n, c from the file" << endl;
			inputFile.close();
			return false;
		}
		cout << "Get the data successfully: " << endl;
		cout << "n = " << n << endl;
		cout << "c = " << c << endl;
		cout << "S: ";
		int temp;
		for (int i = 0; i < n; i ++ ) {
			inputFile >> temp;
			cout << temp << " ";
			finalSum += temp;
			s.push_back(temp);
			temp = INVALID; // security
		}
		
		if (s.size() != n) {
			cout << "Cannot get S from the file successfully" << endl;
			inputFile.close();
			return false;
		}
		cout << endl;
		
		bestx.resize(n, false);
		
		inputFile.close();
		return true;
	}
	
	bool backtrack(int t) {
		if (bestw == c) {
			return true;
		}
		
		if (t >= n) {
			return false;
		}
		
		finalSum -= s[t];
		
		if (bestw + s[t] <= c) {
			bestx[t] = true;
			bestw += s[t];
			if (backtrack(t + 1)) {
				return true;
			}
			bestw -= s[t];
		}
		
		if (bestw + finalSum >= c) {
			bestx[t] = false;
			if (backtrack(t + 1)) {
				return true;
			}
		}
		
		finalSum += s[t]; // add back
		
		
		return false; // No solution
	}
	
	void output() {
		ofstream outputFile(OUTPUT_FILE);
		
		if (!outputFile.is_open()) {
			cout << "Cannot create file to write answer" << endl;
		}
		else {
			cout << "Write anser into file output.txt" << endl;
		}
		
		if (!backtrack(0)) {
			cout << "No solution!" << endl;
			outputFile << "No Solution!";
			outputFile.close();
			return;
		}
		
		cout << "Get answer successfully: " << endl;
		for (int i = 0; i < n; i ++ ) {
			if (bestx[i]) {
				cout << s[i] << " ";
				outputFile << s[i] << " ";
			}
		}
		cout << endl;
		
		
		outputFile.close();
	}
};


int main() {
	Solution solution;
	
	if (solution.input()) {
		solution.output();
	}
	
	return 0;
}
