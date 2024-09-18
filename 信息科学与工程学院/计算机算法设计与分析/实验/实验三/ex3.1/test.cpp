#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> res;
	
	bool dfs(const vector<int>& nums, const int& c, int i) {
		for(int j = i + 1; j < nums.size(); j ++) {
			if(curSum + nums[j] > c) return false;
			else {
				curSum += nums[j];
				res.emplace_back(nums[j]);
				if(curSum == c || dfs(nums, c, j))
					return true;
				curSum -= nums[j];
				res.pop_back();
			}
		}
		return false;
	}
	
private:
	int curSum = 0;	
};
