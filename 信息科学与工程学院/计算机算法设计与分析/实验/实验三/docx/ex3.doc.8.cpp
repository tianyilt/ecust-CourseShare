/**
 * 8«Ú §∏∫
 **/

#include <iostream>

using namespace std;

class Solution {
private:
	int n;
	int yellow;
	int red;
	char c;

public:
	bool input() {
		cin >> n;
		if (n == 0) {
			return false;
		}
		getchar(); // ªª–– 
		
		return true;
	}
	
	void work() {
		red = yellow = 0;
		for (int i = 0; i < n; i ++ ) {
			scanf("%c", &c);
			if (c == 'R') {
				red ++;
			}
			else if (c == 'Y') {
				yellow ++ ;
			}
		}
	}
	
	void output() {
		if (c == 'B') {
			printf("%s\n", (red == 7) ? "Red" : "Yellow");
		}
		else if (c == 'L') {
			printf("%s\n", (yellow == 7) ? "Yellow" : "Red");
		}
	}
};

int main() {
	Solution solution;
	
	while (solution.input()) {
		solution.work();
		solution.output();
	}
	
	return 0;
}
