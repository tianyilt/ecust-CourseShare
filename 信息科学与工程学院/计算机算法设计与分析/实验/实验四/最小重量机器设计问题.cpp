#include<bits/stdc++.h>

using namespace std;

int n;                            //部件数
int m;                            //供应商数
int d;                            //限定价格
int w[100][100];                  //w[i][j]表示第i个零件在第j个供应商的重量
int c[100][100];                 //c[i][j]表示第i个零件在第j个供应商的价格
int bestx[100];                 //表示一次搜索到底后的最优解，用来存放第i个零件的供应商，
int x[100];                     //x[i]临时存放第i个零件的供应商
int cw = 0;                     //当前重量
int cp = 0;                     //当前价格
int bestw = 10000;              //最小重量

void Backtrack(int t) {
    if (t > n)                     //搜索到叶子结点，一个搜索结束，所有零件已经找完
    {
        bestw = cw;                //当前最小重量
        for (int j = 1; j <= n; j ++)
            bestx[j] = x[j];
    }
    else {
        for (int j = 1; j <= m; j ++) {
            x[t] = j;
            cp = cp + c[t][j];
            cw = cw + w[t][j];
            if (cp <= d && cw < bestw)      //剪枝
                Backtrack(t + 1);
            cp = cp - c[t][j];                  //回溯
            cw = cw - w[t][j];
        }
    }
}

int main()
{
    cin >> n >> m >> d;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            cin >> c[i][j];

    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            cin >> w[i][j];

    Backtrack(1);
    cout << bestw << endl;
    for (int i = 1; i <= n; i ++)
        cout << bestx[i] << ' ';
    return 0;
}