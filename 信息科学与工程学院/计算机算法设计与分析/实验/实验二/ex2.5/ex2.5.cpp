#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Solution {
private:
	ifstream inputFile;
	ofstream outputFile;
	const string INPUT_FILE = "input.txt";
	const string OUTPUT_FILE = "output.txt";
	
	int x, k, big;
	int num[100010][4];
	const int MAX = 1e5 + 1;
	/**
	 * num[i][0] : 到i的最小步数
	 * num[i][1] : i的最小数字
	 * num[i][2] : i的最大数字
	 * num[i][3] : i数字和
	 **/
	void count(int i,int j) //num[j]含有数字i,更新num[j]
	{
	    if (i < num[j][1]) {
			num[j][1] = i;
	    }
	    if (i > num[j][2]) {
			num[j][2] = i;
		}
	    num[j][3]+=i;
	}
	
	int getWidgits(int x) {
		int res = 0;
		
		while (x) {
			res += 1;
			x /= 10;
		}
		
		return res;
	}
	
	int getMaxValueOfOperation() {
		big = 81 * getWidgits(x) + 9;
		if (big < 171) {
			big = 171;
		}
		return big;
	}
	
	inline int ctoi(char x) {
		return (int)x - '0';
	}
	
public:
	Solution() {
		inputFile.open(INPUT_FILE);
		if (!inputFile.is_open()) {
			cout << "Failed to open file." << endl;
		}
		outputFile.open(OUTPUT_FILE);
		if (!outputFile.is_open()) {
			cout << "Failed to open file." << endl;
		}
	}
	
	~Solution() {
		inputFile.close();
		if (inputFile.is_open()) {
			cout << "Failed to close input file." << endl;
		}
		
		outputFile.close();
		if (outputFile.is_open()) {
			cout << "Failed to close file." << endl;
		}
	}
	
	bool input() {
		if (!inputFile.is_open()) {
			cout << "The file do not open." << endl;
			return false;
		}
		inputFile >> x >> k;
		cout << "Get data from the file successfully." << endl;
		cout << "x: " << x << endl;
		cout << "k: " << k << endl;
		
		if (!(x | k)) {
			return false;
		}
		return true;
	}
	
	void init() {
		memset(num, 0, sizeof(num));
		
		int big = getMaxValueOfOperation();
		int len = getWidgits(x);
		cout << "len: big : " << len << " " << big << endl;
		
		string s1 = to_string(x);
		for (int i = 0; i <= big; i ++ ) {
			num[i][0] = MAX;//步数初始化为MAX
	        num[i][1] = MAX;
	        num[i][2] = 0;
	        num[i][3] = 0;
		}
		
		for(int i = 0; i < len; i ++ ) {//num[0]存x
			count(ctoi(s1[i]), 0);
		}
		
		num[0][0] = 0;
		
		for(int i = 1; i <= big; i ++ )//预处理1-big每一个数的num[i]
	    {
	        int t = i;
	        while ( t > 0)
	        {
	            int j = t % 10;
	            t /= 10;
	            count(j,i);
	        }
	    }
	}
	
	int compute() {
		if (k == x) {
			return 0;
		}
		if (k > big) {
			return -1;
		}
		bool flag = true;
		
		while (flag) {
			flag = false;
	        for(int i = 0; i <= big; i ++ )
	        	if (num[i][0] < MAX)
	       			for (int k = 0; k <= big; k ++ )
	        			if (num[k][0] < MAX)
	        			{
	            			int j = num[i][3] * num[k][2] + num[k][1];//j=i@k
				            if(num[i][0]+num[k][0]+1<num[j][0])
				            {
				                num[j][0]=num[i][0]+num[k][0]+1;//更新
				                flag=true;
				            }
	        			}
		}
		
		if (num[k][0] < MAX) {
			return num[k][0];
		}
		
		return -1;
	}
	
	void output(int a) {
		if (a == -1) {
			cout << "No answer." << endl;
		}
		else {
			cout << "Get answer: " << a << endl;
		}
		outputFile << a << endl;
		
		cout << "Write the data into file." << endl;
	}
};


int main() {
	Solution solution;
	
	while (solution.input()) {
		solution.init();
		int ans = solution.compute();
		solution.output(ans);
	}
	
	return 0;
}
