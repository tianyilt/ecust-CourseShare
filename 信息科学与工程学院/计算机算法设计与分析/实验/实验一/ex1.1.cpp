#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace std;

class Solution {
private:
	int count_in_range(vector<int>& nums, int target, int l, int r) {
		int count(0);
		for (int i = l; i <= r; i ++ ) {
			if (nums[i] == target) {
				count ++;
			}
		}
		
		return count;
	}
	int majority_element_rec(vector<int>& nums, int l, int r) {
		if (l == r) {
			return nums[l];
		}
		int mid = (l + r) >> 1;
		int left_majority = majority_element_rec(nums, l, mid);
		int right_majority = majority_element_rec(nums, mid + 1, r);
		if (count_in_range(nums, left_majority, l, r) > (r - l + 1) / 2) {
			return left_majority;
		}
		if (count_in_range(nums, right_majority, l, r) > (r - l + 1) / 2) {
			return right_majority;
		}
		
		return -1;
	}
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};

int main() {
	vector<int> nums;
	int num;
	while (cin >> num) {
		nums.push_back(num);
	}
	Solution solution;
	cout << solution.majorityElement(nums) << endl;
	
	system("pause");
	return 0;
}
