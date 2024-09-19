#include <iostream>

using namespace std;

class Solution {
public:
	void getMaxSum_Dp() {
		int T, n, a, i, j;
		cin >> T;
		
		for (j = 1; j <= T; j ++ ) {
			cin >> n;
			int sum(0), maxSum(-1001), first(0), last(0), temp(1);
			
			for (i = 0; i < n; i ++ ) {
				cin >> a;
				sum += a;
				if (sum > maxSum) {
					maxSum = sum;
					first = temp;
					last = i + 1;
				}
				if (sum < 0) {
					sum = 0;
					temp = i + 2;
				}
			}
			
			cout << "Case " << j << ":" << endl;
			cout << maxSum << " " << first << " " << last << endl;
			if (j != T) {
				cout << endl;
			}
		}
	}
};

int main() {
	Solution solution;
	
	solution.getMaxSum_Dp();
	
	return 0;
}
