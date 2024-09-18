#include <iostream>
#include <vector>

using namespace std;

/**
 * 本题目相当没有必要用分治
 * 但是处于分治的题目中，还是勉勉强强用一下分治
 **/
class Solution {
private:
	const static int NUM = 12;
public:
	void getInput(vector<float>& input) {
		for (int i = 0; i < NUM; i ++ ) {
			float money;
			scanf("%f", &money);
			input.push_back(money);
		}
	}
	float calculateSum(vector<float> input, int start, int end) {
		if (start == end) {
			return input[start];
		}
		else {
			int mid = (start + end) >> 1;
			float leftSum = calculateSum(input, start, mid);
			float rightSum = calculateSum(input, mid + 1, end);
			
			return leftSum + rightSum;
		}
	}
	float getAverage(vector<float> input) {
		return calculateSum(input, 0, input.size() - 1) / NUM;
	}
};

int main() {
	Solution solution;
	vector<float> input;
	
	solution.getInput(input);
	printf("$%.2f", solution.getAverage(input));
	
	return 0;
}
