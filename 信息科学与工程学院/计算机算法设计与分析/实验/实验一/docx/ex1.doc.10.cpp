#include <iostream>

using namespace std;


/**
 * 递归做法提交acm超时
 * 
 * 3 ^ n - 1
 **/
 
class Solution {
private:
	int count = 0;
	void move(char begin, char end) {
		cout << begin << "->" << end << endl;
	}
	// 快速幂
	long long int mPow_rc(int a, int b) {
		if (b == 0 && a != 0) {
			return 1;
		}
		if (!a && b) {
			return 0;
		}
		long long int temp = mPow_rc(a, b / 2);
		return b % 2 == 0 ? temp * temp : temp * temp * a;
	}
	
	long long int mPow(int a, int b) {
		if (!b && a) {
			return 1;
		}
		if (!a && b) {
			return 0;
		}
		long long res(1);
		long long temp = static_cast<long long int> (a);
		while (b) {
			if (b % 2 == 1) {
				res *= temp;
			}
			temp *= temp;
			b /= 2;
		}
		
		return res;
	}
	
public:
	void resetCount() {
		count = 0;
	}
	
	// recursion 
	long long int hanoi_rc(int n, char start, char temp, char end) {
		if (n == 1) {
//			move(start, temp);
//			move(temp, end);
			count += 2;
		}
		else {
			hanoi_rc(n - 1, start, temp, end);
//			move(start, temp); 
			count ++;
			hanoi_rc(n - 1, end, temp, start);
//			move(temp, end);
			count ++;
			hanoi_rc(n - 1, start, temp, end);
		}
		return count;
	}
	
	long long int hanoi(int n) {
		return mPow_rc(3, n) - 1;
	}
};

int main() {
	Solution solution;
	
	int n;
	while (cin >> n && n > 0) {
//		cout << solution.hanoi_rc(n, 'a', 'b', 'c') << endl;
		cout << solution.hanoi(n) << endl;
		solution.resetCount();
	}
	
	return 0;
}
