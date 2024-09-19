#include <stdio.h>

using namespace std;

/**
 * 这道题本质是判断step 和 mod的最大公约数是否为1
 * 用辗转相除法
 **/


class Solution {
public:
	// the Greatest Common Divisor (GCD)
	int getGCD(int a, int b) {
		int t;
		
		while (b) {
			t = a % b;
			a = b;
			b = t;
		}
		
		return a;
	}
	
	int getGCD_RECURSION(int a, int b) {
		if (b == 0) {
			return a;
		}
		else {
			return getGCD_RECURSION(b, a % b);
		}
	}
};

int main() {
	int step, mod;
	Solution solution;
	
	while (scanf("%d%d", &step, &mod) == 2) {
		printf("%10d%10d", step, mod);
		if (solution.getGCD_RECURSION(step, mod) == 1) {
			printf("    Good Choice\n");
		}
		else {
			printf("    Bad Choice\n ");
		}
	}
	
	return 0;
}
