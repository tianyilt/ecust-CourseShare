#include <iostream>
#include <iomanip>

using namespace std;

class Solution {
private:
	double e;
	
	int getFactorial(int number) {
		if (number == 0) {
			e += 1;
			cout << number << " " << e << endl;
			return 1;
		}
		int ans = number * getFactorial(number - 1);
		e += (double) (1.000 / (double)ans);
		if (e < 2.6) {
			cout << number << " " << e << endl;
		}
		else {
			cout.setf(ios::showpoint);
			cout << number << " " << setprecision(10) << e;
			if (number < 9) {
				cout << endl;
			}
		}
		return ans;
	}
public:
	double calculateE(int number) {
		 getFactorial(number);
		 
		 return e;
	}
};

int main() {
	cout << "n e\n";
	cout << "- -----------\n";
	Solution solution;
	
	solution.calculateE(9);
	
	return 0;
}
