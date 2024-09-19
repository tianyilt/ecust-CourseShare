#include <iostream>

using namespace std;


/**
 * f_dac(int) 采用递归法, f(int) 用dp
 * 本题目虽然在递归章节中，但是采用递归法时间太长了
 * hdu网站上过不了
 **/
 
class Solution {
private:
	int a, b;
public:
	void setAB(int a_, int b_) {
		a = a_;
		b = b_;
	}
	// 分治法
	int f_dac(int n) {
		if (n == 1) {
			return 1;
		}
		if (n == 2) {
			return 1;
		}
		if (n > 51) {
			int temp = (n - 2) % 49;
			if (temp == 0) {
				temp = 49;
			}
			n = 2 + temp;
		}
		return (a * f_dac(n - 1) + b * f_dac(n - 2)) % 7;
	}
	// DP
	int f(int n) {
		if (n == 1 || n == 2) {
			return 1;
		}
		int prev1(1), prev2(1);
		int result;
		
		// 2 + 49(7 * 7)
		if (n > 51) {
			int temp = (n - 2) % 49;
			if (temp == 0) {
				temp = 49;
			}
			n = 2 + temp;
		}
		
		for (int i = 3; i <= n; i ++ ) {
			result = (a * prev1 + b * prev2) % 7;
			prev2 = prev1;
			prev1 = result; 
		}
		
		return result;
	}
};

int main() {
	int a, b;
	long long n;
	Solution solution;
	
	while (cin >> a >> b >> n && (a || b || n)) {
		solution.setAB(a, b);
		cout << solution.f(n) << endl;
//		cout << solution.f_dac(n) << endl;
	}
	
	return 0;
}
