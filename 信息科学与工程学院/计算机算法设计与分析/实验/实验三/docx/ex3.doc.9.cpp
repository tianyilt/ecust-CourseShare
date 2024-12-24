/**
 * DFS
 **/

#include <iostream>

using namespace std;

class Solution {
private:
	long long factorial(long long n) {
		long long res(1);
		
		for (long long i = 1; i <= n; i ++ ) {
			res = res * i;
		}
		
		return res;
	}
	
public:
	/**
	 * @brief 可以经过数学证明前面10位数字只存在四个数
	 * 并且如果遍历到2147483647，那么hdu上肯定超时过不了
	 * 
	 **/
	void work() {
		long long sum(0), res(0);
		for (long long i = 1; i <= 43432; i ++ ) {
			res = i;
			sum = 0;
			while (res) {
				sum += (factorial(res % 10));
				res /= 10;
			}
			if (sum == i) {
				printf("%lld\n", i);
			}
		}
	}
};

int main() {
	Solution solution;
	solution.work();
	
	return 0;
}
