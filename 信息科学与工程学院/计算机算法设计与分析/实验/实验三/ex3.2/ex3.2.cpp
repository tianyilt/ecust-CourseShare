/**
 * 5-2 最小长度电路板排列问题
 **/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Solution {
private:
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output.txt";
	const int INVALID = -1;
	
	int n;
	int m;
	vector<vector<int>> B;
	vector<int> bestx; // 最终的最优解排列顺序
	vector<int> x, low, high; // 当前的排列、最左边的排列、最右边的排列
	int bestd; // 最优解
	
	int len(int); // 计算当前i排列的最小长度
	void backtrack(int); 
public:	
	Solution() {
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
				"8 5\n"
				"1 1 1 1 1\n"
				"0 1 0 1 0\n"
				"0 1 1 1 0\n"
				"1 0 1 1 0\n"
				"1 0 1 0 0\n"
				"1 1 0 1 0\n"
				"0 0 0 0 1\n"
				"0 1 0 0 1";
			output << content;
			output.close();
		}
		
		inputFile.close();		
	}

	// 懒人写法，方便打印数字
	friend ostream& operator<<(ostream& out, vector<int>& array);

	bool input() {
		ifstream inputFile(INPUT_FILE);
		
		if (!inputFile.is_open()) {
			cout << "Cannot open file input.txt" << endl;
		}
		
		inputFile >> n >> m;
		if (n == INVALID || m == INVALID) {
			cout << "Cannot get the value of n, m from the file" << endl;
			inputFile.close();
			return false;
		}
		cout << "Get the data successfully: " << endl;
		cout << "n = " << n << endl;
		cout << "m = " << m << endl;
		
		B.resize(n, vector<int>(m, 0));
		cout << "B: " << endl;
		
		for (int i = 0; i < n; i ++ ) {
			for (int j = 0; j < m; j ++ ) {
				inputFile >> B[i][j];
				cout << B[i][j] << " ";
			}
			cout << endl;
		}
		
		inputFile.close();
		
		if (B.size() != n || B[0].size() != m) {
			cout << "文件中B的输入不对" << endl;
			return false;
		}
		
		bestd = 0;
		bestx.resize(n);
		x.resize(n + 1), low.resize(n + 1), high.resize(n + 1);
		
		return true;
	}
	
	void output() {
		ofstream outputFile(OUTPUT_FILE);
		if (!outputFile.is_open()) {
			cout << "Cannot open the file." << endl;
		}
		
		int ans = arrangeBoards();
		
		cout << "Get answer successfully: " << endl;
		cout << ans << endl;
		
		outputFile << ans << endl;
		for (const int & num : bestx) {
			cout << num << " ";
			outputFile << num << " ";
		}
		cout << endl;
		cout << "成功写入数据" << endl;
		
		outputFile.close();
		// 打开文件
		// system("notepad input.txt");
		// system("notepad output.txt"); 
	}
	
	vector<int> getBestx() const {
		return bestx;
	}
	
	int arrangeBoards() {
		bestd = n + 1;
		for (int i = 1; i <= n; i ++ ) {
			x[i] = i;
		}
		backtrack(1);
		
		return bestd;
	}
};

ostream& operator<<(ostream& out, vector<int>& array) {
	int n = array.size();
	for (int i = 0; i < n; i ++ ) {
		out << array[i] << ' ';
	}
	out << endl;
	
	return out;
		
}

int main() {
	Solution solution;
	solution.input();
	
	solution.output();
	
	return 0;
}

int Solution::len(int ii) {
	for (int i = 1; i <= m; i ++ ) {
		high[i] = 0;
		low[i] = n + 1;
	}
	for (int i = 1; i <= ii; i ++ ) {
		for (int k = 1; k <= m; k ++ ) {
			if (B[x[i] - 1][k - 1] > 0) {
				if (i < low[k]) {
					low[k] = i;
				}
				if (i > high[k]) {
					high[k] = i;
				}
			}
		}
	}
	int tmp = 0;
	for (int k = 1; k <= m; k ++ ) {
		if (low[k] <= n && high[k] > 0 && tmp < high[k] - low[k]) {
			tmp = high[k] - low[k];
		}
	}
	
	return tmp;
}

void Solution::backtrack(int i) {
	if (i == n) {
		int tmp = len(i);
		if (tmp < bestd) {
			bestd = tmp;
			for (int j = 1; j <= n; j ++ ) {
				bestx[j - 1] = x[j];
			}
		} 
	}
	else {
		for (int j = i; j <= n; j ++ ) {
			swap(x[i], x[j]);
			int ld = len(i);
			if (ld < bestd) {
				backtrack(i + 1);
			}
			swap(x[i], x[j]);
		}
	}
}
