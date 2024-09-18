#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	const long long int MOD = 1e9 + 7;
	vector<vector<long long int>> dp;
	// dp[i][0] 表示第i个为G
	// dp[i][1] 表示第i个为R
	// dp[i][2] 表示第i个为P
public:
	// G至多u个连续，R至多连续v个
	long long int cal(long long int n, long long int u, long long int v) {
		int i;
		dp[0][1] = dp[0][0] = 0;
		dp[0][2] = 1;
		
		for (i = 1; i <= n; i ++ ) {
			long long int sum = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % MOD;
			dp[i][2] = sum;
			if (i <= u) {
				dp[i][0] = sum;
			}
			else if (i == u + 1) {
				dp[i][0] = (sum - 1) % MOD;
			}
			else {
				dp[i][0] = (sum - dp[i - u - 1][1] - dp[i - u - 1][2]) % MOD;
			}
			
			if (i <= v) {
				dp[i][1] = sum;
			}
			else if (i == v + 1) {
				dp[i][1] = (sum - 1) % MOD;
			}
			else {
				dp[i][1] = (sum - dp[i - v - 1][0] - dp[i - v - 1][2]) % MOD;
			}
		}
		
		return (dp[n][0] + dp[n][1] + dp[n][2]) % MOD;
	}
	
	long long int getWaysToArrange(long long int n, long long int m, long long int k) {
		dp.resize(n + 1, vector<long long int> (3, 0));
		long long int ans = cal(n, n, k);
		
		ans = ((ans - cal(n, m - 1, k)) % MOD + MOD) % MOD;  
		//注意减法可能出现负数，取模的时候要特别处理一下。
		
		return ans;
	}
};

int main() {
	long long int n, m, k;
	Solution solution;
	
	while (scanf("%lld%lld%lld", &n, &m, &k) == 3) {
		cout << solution.getWaysToArrange(n, m, k) << endl;
	}
	
	return 0;
}
