#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

class Solution {
private:
	void dfs(string& s, int start, int end, int& maxPos, int& maxLen) {
		if (start >= end) {
			return;
		}
		
		int lower(0), upper(0);
		for (int i = start; i <= end; i ++ ) {
			if (islower(s[i])) {
				lower |= 1 << (s[i] - 'a');
			}
			else {
				upper |= 1 << (s[i] - 'A');
			}
		}
		
		if (lower == upper) {
			if (end - start + 1 > maxLen) {
				maxPos = start;
				maxLen = end - start + 1;
			}
			return;
		}
		
		int valid = lower & upper; // ºÏ·¨µÄ×Ö·û
		int pos(start);
		while (pos <= end) {
			start = pos;
			while (pos <= end && valid & (1 << (tolower(s[pos]) - 'a'))) {
				pos ++;
			}
			dfs(s, start, pos - 1, maxPos, maxLen);
			pos ++;
		}
	}
public:
	string longestNiceSubstring(string s) {
		int maxPos(0), maxLen(0);
		int start(0), end(s.length() - 1);
		
		dfs(s, start, end, maxPos, maxLen);
		
		return s.substr(maxPos, maxLen);
	}
};

int main() {
	Solution solution;
	string s;
	
	cout << "s = ";
	cin >> s;
	
	cout << solution.longestNiceSubstring(s) << endl;
	
	system("pause");
	return 0;
}
