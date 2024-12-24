#include <iostream>

using namespace std;

/**
 * 九余数定理
 * n*n不断取数字根相乘所得结果便是n^n的数字根
 **/

class Solution {
private:
	// n ^ n
	int getRoot(int n) {
		int digital(0);
		
		while (n) {
			digital += n % 10;
			n /= 10;
		}
		if (digital > 9) {
			return getRoot(digital);
		}
		return digital;
	}
public:
	void digitalRoots() {
		int n, m, k;
		while (cin >> n && n) {
			k = getRoot(n);
			for (m = 1; m < n; m ++ ) {
				k = n * getRoot(k);
			}
			k = getRoot(k);
			printf("%d\n", k);
		}
	}
	
	// The Theorem of Nine Remainders
	void digitalRoots_NR() {
		int n, a;
		while (cin >> n && n) {
			a = 1;
			for (int i = 0; i < n; i ++ ) {
				a = a * n % 9;
				if (a == 0) {
					a = 9;
				}
			}
			cout << a << endl;
		}
	}
};

int main() {
	Solution solution;
//	solution.digitalRoots();
	solution.digitalRoots_NR();
	
	
	return 0;
}
