/**
 * 组合总数
 **/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Solution {
private:
    // dfs(candidates,target,combine,idx)
	// candidates数组的第 idx位
	// 还剩 target 要组合
	// 已经组合的列表为 combine
    void dfs(vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& combine, int idx) {
        if (idx == candidates.size()) {
            return;
        }

        if (target == 0) {
            ans.emplace_back(combine);
            return;
        }

        dfs(candidates, target, ans, combine, idx + 1);

        if (target - candidates[idx] >= 0) {
            combine.emplace_back(candidates[idx]);
            dfs(candidates, target - candidates[idx], ans, combine, idx);
            combine.pop_back();
        }
    }

	// 读取一行内的输入
	void inputArrays(vector<int>& input) {
		string line;
		while (getline(cin, line)) {		
			if (line.empty()) {
				continue;
			}
			
			istringstream iss(line);
			int num;
			
			while (iss >> num) {
				input.push_back(num);
			}
			
			break;
		}
	}
		
	
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combine;
        dfs(candidates, target, ans, combine, 0);
        return ans;
    }
    
    void input(vector<int>& candidates, int& target) {
		cout << "请输入数组candidates:(一行)" << endl;
		inputArrays(candidates);
		cout << "请输入目标数target: "  << endl;
		cin >> target;
	}
	
	void output(vector<vector<int>> ans) {
		cout << "答案如下：" << endl;
		for (const vector<int> & p : ans) {
			for (const int & num : p) {
				cout << num << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	Solution solution;
	vector<int> candidates;
	int target;
	
	solution.input(candidates, target);
	vector<vector<int>> ans = solution.combinationSum(candidates, target);
	solution.output(ans);
	
	return 0;
}

