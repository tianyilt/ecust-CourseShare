#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

int dp[200][1000];
//dp[i][j] 表示前i个作业中A机器花j分钟的时候 B机器所花时间 


/**
 * 此程序不知为何有bug，在32位系统的编辑器中，得不出答案
 * 在64位是完全可以正常运行的
 * 可能的原因是：32位系统无法完全兼容动态编译？
 * 
 * 破案了，数组逾界 -1
 **/

class Solution {
private:
	int n; // 作业数目
	vector<int> a; // 每个作业A的时间
	vector<int> b; // 每个作业B的时间
public:
	void input(const string fileName) {
		ifstream inputFile(fileName);
		if (!inputFile.is_open()) {
			cout << "Failed to open the file." << endl;
		}
		inputFile >> n;
		
		a.resize(n);
		for (int i = 0; i < n; i ++ ) {
			inputFile >> a[i];
		}
		
		b.resize(n);
		for (int i = 0; i < n; i ++ ) {
			inputFile >> b[i];
		}
		
		inputFile.close();
		cout << "数据获取成功：" << endl;
		textOutput();
	}
	
	void output(int ans, const string fileName) {
		ofstream outputFile(fileName);
		if (!outputFile.is_open()) {
			cout << "Failed to open the file." << endl;
		}
		cout << "答案获取成功：";
		cout << ans << endl;
		
		outputFile << ans;
		
		outputFile.close();
		cout << "数据已存入文件：" << endl;
	}
	
	int minTime() {
		// vector<vector<int>> dp(n + 1, vector<int>(201, 0)); 
		// dp[i][j] 表示前i个作业中A机器花j分钟的时候 B机器所花时间 
		
		int sum = 0;
		for (int i = 1; i <= n; i ++ ) {
			sum += a[i - 1];
			for (int j = 0; j <= sum; j ++ ) {
				dp[i][j] = dp[i - 1][j] + b[i - 1];
				if (j >= a[i - 1]) {
					dp[i][j] = min(dp[i - 1][j] + b[i - 1], dp[i - 1][j - a[i - 1]]);
				}
			}
		}
		
		int ans = 5000;
		for (int i = 0; i <= sum; i ++ ) {
			ans = min(ans, max(dp[n][i], i));
		}
		
		return ans;
	}
	
	
	void textOutput() {
		cout << "n: " << n << endl;
		cout << "a: ";
		for (vector<int>::iterator it = a.begin(); it != a.end(); it ++ ) {
			cout << *(it) << " ";
		}
		cout << endl;
		cout << "b: ";
		for (vector<int>::iterator it = b.begin(); it != b.end(); it ++ ) {
			cout << *(it) << " ";
		}
		cout << endl;
	}
};

int main() {
	memset(dp, 0, sizeof(dp));
	
	const string INPUT = "input.txt";
	const string OUTPUT = "output.txt"; 
	Solution solution;
	solution.input(INPUT);
    // solution.textOutput();
    int ans = solution.minTime();
    solution.output(ans, OUTPUT);
	
	return 0;
}
