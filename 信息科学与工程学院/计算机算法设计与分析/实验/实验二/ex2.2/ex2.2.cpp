#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * convert circular to linear
 * 1 2 3 -> 1 2 3 1 2 3 
 * repeat twice
 **/

class Solution {
private:
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output.txt";
	vector<int> input;
	int number; // number piles of stones
	vector<int> s; // sum
	int min_score, max_score;
public:
	Solution() {
		ifstream inputFile(INPUT_FILE);
		if (!inputFile.is_open()) {
			cout << "Failed to open the file." << endl;
		}
//		else {
//			cout << "Open the file successfully." << endl;
//		}
		
		inputFile >> number;
		cout << "Get number successfully: " << number << endl;
		
		input.resize(number);
		for (int i = 0; i < number; i ++ ) {
			inputFile >> input[i];
		}
		cout << "Get array successfully: ";
		for (const int & num : input) {
			cout << num << " ";
		}
		cout << endl;
		
		inputFile.close();
		
		// deal vector<int> s
		s.resize(2 * number + 1, 0);
		for (int i = 1; i <= number; i ++ ) {
			s[i] = s[i - 1] + input[i - 1];
		}
		for (int i = number + 1; i <= 2 * number; i ++ ) {
			s[i] = s[i - 1] + input[i - number - 1];
		}
	}
	
	void getScore() {
		vector<vector<int>> f_min(2 * number + 1, vector<int> (2 * number + 1));
		vector<vector<int>> f_max(2 * number + 1, vector<int> (2 * number + 1));	
		for (int i = 0; i <= 2 * number; i ++ ) {
			for (int j = 0; j <= 2 * number; j ++ ) {
				f_min[i][j] = 0x3f;
				f_max[i][j] = -1;
			}
		}
		// The minimum score for merging i~j piles of stones. f_min[i][j]
		
		for (int i = 1; i <= 2 * number; i ++ ) {
			f_min[i][i] = 0;
			f_max[i][i] = 0;
		}
		
		for (int len = 2; len <= number; len ++ ) {
			// i ~ j : as i is the start, while j is the destination
			for (int i = 1; i + len - 1 <= 2 * number; i ++ ) {
				int j = i + len - 1;
				
				for (int k = i; k < j; k ++ ) {
					f_min[i][j] = min(f_min[i][j], f_min[i][k] + f_min[k + 1][j] + s[j] - s[i - 1]);
					f_max[i][j] = max(f_max[i][j], f_max[i][k] + f_max[k + 1][j] + s[j] - s[i - 1]);
				}
			}
		}
		
		min_score = f_min[1][number];
		max_score = f_max[1][number];
		/*
		cout << "test f_min" << endl;
		for (int i = 1; i <= 2 * number; i ++ ) {
			for (int j = 1; j <= 2 * number; j ++ ) {
				cout << f_min[i][j] << " ";
			}
			cout << endl;
		}
		*/
		
		/*
		cout << "test f_max" << endl;
		for (int i = 1; i <= 2 * number; i ++ ) {
			for (int j = 1; j <= 2 * number; j ++ ) {
				cout << f_max[i][j] << " ";
			}
			cout << endl;
		}
		*/
	}
	
	int minScore() const {
		return min_score;
	}
	
	int maxScore() const {		
		return max_score;
	}
	
	void output(int minScore, int maxScore) {
		ofstream outputFile(OUTPUT_FILE);
		if (!outputFile.is_open()) {
			cout << "Failed to open the file." << endl;
		}
		
		cout << "Get min score: " << minScore << endl;
		cout << "Get max score: " << maxScore << endl;
		
		outputFile << minScore << endl << maxScore;
		
		cout << "Write the data into file." << endl;
	}
};

int main() {
	Solution solution;
//	cout << solution.minScore();
//	cout << solution.maxScore();
	solution.getScore(); // get score
	solution.output(solution.minScore(), solution.maxScore());
	
	return 0;
}
