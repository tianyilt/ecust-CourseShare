/**
 * N皇后问题
 **/

#include <iostream>
#include <cmath>

using namespace std;

class Solution {
private:
	int n; 
	int * table; // 打表，将结果存到表中，减少重复运算
	int * chessman; // chessman[i] = j, 表示第i行第j列有棋子
	int ans;
	
	bool judge(int row) {
		for (int i = 1; i < row; i ++ ) {
			if (chessman[i] == chessman[row] || 
				abs(row - i) == abs(chessman[row] - chessman[i])) 
				// 对角线斜率绝对值相等
			{
				return false;
			}
		}
		
		return true;
	}
	
	// 方法一：深搜
	void dfs(int row) {
		if (row == n + 1) {
			ans ++ ;
		}
		else {
			for (int j = 1; j <= n; j ++ ) {
				chessman[row] = j;
				if (judge(row)) {
					dfs(row + 1); // 本行能下棋就接着下
				}
			}
		}
	}
	
	void cnt() {
		dfs(1);
	}
	
	// 回溯算法
	int solve(int n, int row, int columns, int diagonals1, int diagonals2) {
		if (row == n) {
			return 1;
		}
		else {
			int count(0);
			
			int availablePositions = 
				((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
				
			while (availablePositions) {
				int position(availablePositions & (-availablePositions));
				availablePositions = availablePositions & (availablePositions - 1);
				count += solve(n, row + 1, columns | position,
				 (diagonals1 | position) << 1, (diagonals2 | position) >> 1);
			}
			
			return count;
		}
	}
	
public:
	Solution() {
//		table = new int[11];
//		chessman = new int[20];
	}
	
	~Solution() {
//		delete[] table;
//		delete[] chessman;
	}
	
	bool input() {
		cin >> n;
		if (!n) {
			return false;
		}
		
		return true;
	}
	
	// 预处理，防止超时
	// dfs
	void preDeal() {
		for (n = 1; n <= 10; n ++ ) {
			ans = 0;
			cnt();
			table[n] = ans;
		}	
	}
	
	int totalNQueens() {
		return solve(n, 0, 0, 0, 0);
	}
	
	void output() {
		cout << table[n] << endl;
	}
};

int main() {
	Solution solution;
	
	// 深搜
	// solution.preDeal();
	
	while (solution.input()) {
		// 回溯
		cout << solution.totalNQueens() << endl;
	}
	
	return 0;
}
