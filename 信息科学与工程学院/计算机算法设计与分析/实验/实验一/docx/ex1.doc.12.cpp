#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
private:
	vector<vector<int>> inputs;
	vector<int> tmp;
public:
	void initTemp() {
		tmp.resize(1001, 0);
	}
	void inputArrays(vector<int>& input) {
		int n;
		cin >> n;
		
		while (n -- ) {
			int number;
			cin >> number;
			input.push_back(number);
		}
	}
	
	void merge_sort(vector<int>& input, int left, int right) {
		if (left >= right) {
			return;
		}
		
		int mid = (left + right) >> 1;
		
		merge_sort(input, left, mid);
		merge_sort(input, mid + 1, right);
		
		int k = 0, i = left, j = mid + 1;
		while (i <= mid && j <= right) {
			if (input[i] <= input[j]) {
				tmp[k ++ ] = input[i ++ ];
			}
			else {
				tmp[k ++ ] = input[j ++ ];
			}
		}
		
		while (i <= mid) {
			tmp[k ++ ] = input[i ++ ];
		}
		while (j <= right) {
			tmp[k ++ ] = input[j ++ ];
		}
		
		for (i = left, j = 0; i <= right; i ++, j ++ ) {
			input[i] = tmp[j];
		}
	}
	
	void outputArrays(vector<int> input) {
		for (const int & num : input) {
			cout << num << " ";
		}
	}
	
	void addInput(vector<int> input) {
		inputs.push_back(input);
	}
	
	void outputInputs() {
		for (auto input : inputs) {
			outputArrays(input);
			cout << endl;
		}
	}
};

int main() {
	int n;
	Solution solution;
	
	cin >> n;
	
	while (n -- ) {
		vector<int> input;
		solution.initTemp();
		solution.inputArrays(input);
		solution.merge_sort(input, 0, input.size() - 1);
		solution.addInput(input);
	}
	solution.outputInputs();
	
	return 0;
}
