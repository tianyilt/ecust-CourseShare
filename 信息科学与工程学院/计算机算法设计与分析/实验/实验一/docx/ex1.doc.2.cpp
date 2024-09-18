#include <stdio.h>

const int MAX_N = 1010;
int a[MAX_N];

/**
 * 模拟(想不出体现出分治的算法)
 **/

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		int t1(0); // 上升次数
		int t2(0); // 下降次数
		
		for (int i = 1; i <= n; i ++ ) {
			scanf("%d", a + i);
			if (a[i] > a[i - 1]) {
				t1 += a[i] - a[i - 1];
			}
			else if (a[i] < a[i - 1]) {
				t2 += a[i - 1] - a[i];
			}
		}
		printf("%d\n", t1 * 6 + t2 * 4 + n * 5);
	}
	
	return 0;
}
