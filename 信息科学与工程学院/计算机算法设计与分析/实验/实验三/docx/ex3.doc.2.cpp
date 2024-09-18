/**
 * 变形课
 **/
 
#include <cstdio>
#include <cstring>

class Solution {
private:
	char * str;
	char * a; // 首字母
	char * b; // 末字母
	int x; //会的魔法数量
	int k;
	
	void dfs(char r) {
		if (r == 'b') {
			k = 1;
			return;
		}
		for (int j = 0; j < x; j ++ ) {
			if (b[j] == r) {
				dfs(a[j]);
			}
		}
	}

public:
	Solution() {
		str = new char[100];
		a = new char[500];
		b = new char[500];
	}
	~Solution() {
		delete[] str;
		delete[] a;
		delete[] b;
	}
	
	void work() {
		int n, y;
		char m;
		
		while (scanf("%s", str) != EOF) {
			y = strlen(str);
			a[0] = str[0];
			b[0] = str[y - 1];
			x = 1;
			
			for (int i = 1; ; i ++ ) {
				scanf("%s", str);
				if (str[0] == '0') {
					break;
				}
				y = strlen(str);
				a[i] = str[0];
				b[i] = str[y - 1];
				x ++; 
			}
	
			m = 'm'; // 初值
			k = 0;
			dfs(m);
			if (k == 1) {
				printf("Yes.\n");
			}
			else {
				printf("No.\n");
			}
		}
	}
};

int main() {
	Solution solution;
	
	solution.work();
	
	return 0;
}
