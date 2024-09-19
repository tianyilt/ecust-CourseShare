#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	int dfs(string s, int left, int right, int k) {
		vector<int> cnt(26, 0);
		for (int i = left; i <= right; i ++ ) {
			cnt[s[i] - 'a'] ++;
		}
		
		char split = 0; // 不满足条件的字符
		for (int i = 0; i < 26; i ++ ) {
			if (cnt[i] > 0 && cnt[i] < k) {
				split = i + 'a';
			}
		}
		if (split == 0) {
			return right - left + 1;
		}
		
		int res(0);
		int i(left);
		while (i <= right) {
			while (i <= right && s[i] == split) {
				i ++;
			}
			if (i > right) {
				break;
			}
			int start(i);
			while (i <= right && s[i] != split) {
				i ++;
			}
			
			int length = dfs(s, start, i - 1, k);
			res = max(length, res);
		}
		
		return res;
	}
public:
	int longestSubstring(string s, int k) {
		int n = s.length();
		return dfs(s, 0, n - 1, k);
	}
};

int main() {
	string s;
	int k;
	cout << "s = ";
	cin >> s;
	cout << "k = ";
	cin >> k;
	
	Solution solution;
	cout << solution.longestSubstring(s, k) << endl;
	
	system("pause");
	return 0;
}
