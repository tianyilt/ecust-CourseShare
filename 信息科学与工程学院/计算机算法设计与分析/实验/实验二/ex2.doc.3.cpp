#include <stdio.h>
#include <string.h>
#include <algorithm>

#define inf 0x3f3f3f

using namespace std;

int n,x,y,z;
int a[20];
int dp[15][2000];

int main()
{
    while (~scanf("%d",&n) && n)
    {
        int maxx = -1;
        memset(a, 0, sizeof(a));
        scanf("%d%d%d", &x, &y, &z);
        
        for(int i = 1; i <= n; i ++ )
        {
            scanf("%d", &a[i]);
            maxx = max(maxx, a[i]);
        }
        memset(dp, inf, sizeof(dp));
        for(int i = a[1]; i <= maxx; i ++ )
            dp[1][i] = x * i + y * i;
        for(int i = 2; i<=n; i++)
            for(int j = a[i]; j <= maxx; j ++ )
                for(int k = 0; k <= maxx; k ++ )
                {
                    if(k <= j)
                        dp[i][j] = min(dp[i][j], dp[i-1][k] + (j - k) * x + j * y);
                    else
                        dp[i][j]=min(dp[i][j], dp[i-1][k] + (k - j) * z + j * y);
                }
        int num = inf;
        for(int j = 0; j <= maxx; j ++ )
            num = min(num, dp[n][j]);
        printf("%d\n", num);
    }
    return 0;
}
