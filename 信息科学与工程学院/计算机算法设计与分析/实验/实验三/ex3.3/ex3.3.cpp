/**
 * 运动员最佳配对问题
 **/

#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

class Solution {
private:
	const string INPUT_FILE = "input.txt";	
	const string OUTPUT_FILE = "output.txt";
	
	int n;
	vector<vector<int>> P, Q;
	
	int maxSum; // 男女双方竞赛优势的总和的最大值 最终答案
	int sum; // 临时求和
	vector<int> maxSumP; // 每个男生匹配后可达到的最大双方竞赛优势
	vector<bool> bookQ; // 记录女运动员是否已匹配
	vector<vector<int>> data; // 男运动员i配对后女运动员j的优势 data[i][j]
	
	void backTrack(int t) {
		if (t >= n) {
			// 到达n，代表全部标记，得到最大值
			maxSum = max(maxSum, sum);
			return;
		}
		int ctn = 0;
		for (int i = t; i < n; i ++ ) {
			ctn += maxSumP[i];
		}
		if (sum + ctn < maxSum) {
			return;
		}
		for (int i = 0; i < n; i ++ ) {
			if (!bookQ[i]) {
				bookQ[i] = true;
				sum += data[t][i];
				backTrack(t + 1);
				bookQ[i] = false;
				sum -= data[t][i];
			}
		}
	}
	
	void dealData() {
		for (int i = 0; i < n; i ++ ) {
			for (int j = 0; j < n; j ++ ) {
				data[i][j] = P[i][j] * Q[j][i];
				maxSumP[i] = max(maxSumP[i], data[i][j]);
			}
		}
	}
	
public:
	Solution() {
		maxSum = -0xfffff;
		sum = 0;
		
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
				"3\n"
				"10 2 3\n"
				"2 3 4\n"
				"3 4 5\n"
				"2 2 2\n"
				"3 5 3\n"
				"4 5 1\n";
			output << content;
			output.close();
		}
		
		inputFile.close();
		
	}
	
	bool input() {
		ifstream inputFile(INPUT_FILE);
		if (!inputFile.is_open()) {
			cout << "Cannot open the file." << endl;
			return false;
		}
		
		cout << "成功读取数据: " << endl;
		cout << "n: " << endl;
		inputFile >> n;
		cout << n << endl;
		
		P.resize(n, vector<int>(n, 0));
		Q.resize(n, vector<int>(n, 0));
		
		cout << "P: " << endl;
		for (int i = 0; i < n; i ++ ) {
			for (int j = 0; j < n; j ++ ) {
				inputFile >> P[i][j];
				cout << P[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Q: " << endl;
		for (int i = 0; i < n; i ++ ) {
			for (int j = 0; j < n; j ++ ) {
				inputFile >> Q[i][j];
				cout << Q[i][j] << " ";
			}
			cout << endl;
		}
		
		maxSumP.resize(n, 0);
		bookQ.resize(n, false);
		data.resize(n, vector<int>(n, 0));
		
		inputFile.close();
		return true;
	}
	
	void deal() {
		dealData(); // 处理data，初始化处理
		backTrack(0);
	}
	
	void output() {
		deal();
		cout << "Get answer successfully: " << endl;
		cout << maxSum << endl;
		
		ofstream outputFile(OUTPUT_FILE);
		if (!outputFile.is_open()) {
			cout << "Cannot open the file." << endl;
			return;
		}
		outputFile << maxSum << endl;
		cout << "成功写入文件" << endl;
		
		outputFile.close();
		
		/**
		 * 32位编译器不能识别lambda语句，且无法使用thread创建线程
		 * 但64位是可以完成的
		 **/
		// 打开文件
		// 异步操作
		// future<void> future = async(&Solution::showFile, this);
		// 线程法
		/*
		thread t([this]() {
			system("notepad output.txt");
		});
		t.detach();
		Sleep(1000);
		*/
	}
};

int main() {
	Solution solution;	
	if (solution.input()) {
		solution.output();
	}
	return 0;
}
