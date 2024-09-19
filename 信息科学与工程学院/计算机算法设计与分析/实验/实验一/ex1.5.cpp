#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
private:
    void quick_sort(vector<int>& q, int left, int right, vector<int>& ans, int& count, int cnt)
    {
        if (left >= right) {
            if (count < cnt) {
                ans.push_back(q[left]);
                count ++;
            }
            return;
        }

        int i = left - 1, j = right + 1;
        int x = q[(left + right) >> 1];
        while (i < j) {
            do i ++; while (q[i] < x);
            do j --; while (q[j] > x);
            if (i < j) {
                swap(q[i], q[j]);
            }
        }
        quick_sort(q, left, j, ans, count, cnt), quick_sort(q, j + 1, right, ans, count, cnt);
    }
public:
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
	
    vector<int> inventoryManagement(vector<int>& stock, int cnt) {
        vector<int> ans;
        int count(0);
        quick_sort(stock, 0, stock.size() - 1, ans, count, cnt);

        return ans;
    }
};

int main() {
	Solution solution;
	vector<int> ans;
	
	vector<int> stock;
	int cnt;
	
	cout << "stock: ";
	solution.inputArrays(stock);
	cout << "cnt: ";
	cin >> cnt;
  	
	ans = solution.inventoryManagement(stock, cnt);
	
	for (const int & num : ans) {
		cout << num << " ";
	}
	cout << endl;
	
	system("pause");
	return 0;
}
