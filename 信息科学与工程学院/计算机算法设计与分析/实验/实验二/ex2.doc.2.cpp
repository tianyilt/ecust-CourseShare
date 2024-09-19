#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	vector<double> r; // the probability of getting caught from robbing of each bank
	vector<int> n; // the amount owned by each bank
	
	void testInput() {
		cout << "test n, r\n";
		for (const int & i : n) {
			cout << i << " ";
		}
		cout << endl;
		for (const double & p : r) {
			cout << p << " ";
		}  
		cout << endl;

	}
public:
	int work_2d_dp(double rate, int number) {
		r.clear();
		n.clear();
		
		int res(0);
		
		float temp_r;
		int temp_n;
		int sum_n(0);
		
		for (int k = 0; k < number; k ++ ) {
			cin >> temp_n >> temp_r;
			sum_n += temp_n;
			n.emplace_back(temp_n);
			r.emplace_back(temp_r); 
		}
		
//		cout << "sum_n: " << sum_n << endl;
		
		// f[number][sum_n]  i banks the sums equal j
		// f[i][j] The probability of not being caught stealing i banks with an amount of n
		vector<vector<double>> f(number + 1, vector<double>(sum_n + 1, 0.0));
		
		for (int i = 0; i <= number; i ++ ) {
			f[i][0] = 1;
		}
		// when he stole no money, the probability of not being caught is 1;
		
		for (int i = 1; i <= number; i ++ ) {
			for (int j = 1; j <= sum_n; j ++ ) {
				if (j < n[i - 1]) {
					f[i][j] = f[i - 1][j];
				}
				else {
					f[i][j]	= max(f[i - 1][j], f[i - 1][j - n[i - 1]] * (1 - r[i - 1]));
				}
				if (f[i][j] >= (1 - rate) && res < j) {
					res = j;
				}
			}
		}
		/*
		for (int i = 1; i <= number; i ++ ) {
			for (int j = 1; j <= sum_n; j ++ ) {
				cout << f[i][j] << " ";
			}
			cout << endl;
		}
		*/
		
		
		return res;
	}
	
	int work_dp(double rate, int number) {
		r.clear();
		n.clear();
		
		int res(0);
		
		float temp_r;
		int temp_n;
		int sum_n(0);
		
		for (int k = 0; k < number; k ++ ) {
			cin >> temp_n >> temp_r;
			sum_n += temp_n;
			n.emplace_back(temp_n);
			r.emplace_back(temp_r); 
		}
		
//		cout << "sum_n: " << sum_n << endl;
		
		// f[[j] The probability of not being caught stealing with an amount of n
		vector<double> f(sum_n + 1, 0.0);
		
		f[0] = 1;
		// when he stole no money, the probability of not being caught is 1;
		
		for (int i = 0; i < number; i ++ ) {
			for (int j = sum_n; j >= n[i]; j -- ) {
				f[j] = max(f[j], f[j - n[i]] * (1 - r[i]));
				// do not stole or stole, and calculate the probability
			}
		}
		
		for (int i = sum_n; i >= 0; i -- ) {
			if (f[i] >= (1 - rate)) {
				res = i;
				break;
			}
		}
		
		return res;
	}
};

int main() {
	int number;
	Solution solution;
	
	cin >> number;
	
	while (number -- ) {
		double rate;
		int n;
		cin >> rate >> n;
//		cout << solution.work_2d_dp(rate, n) << endl;
		cout << solution.work_dp(rate, n) << endl;
	}
	
	return 0;
}
