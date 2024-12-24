#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

const int INF = 100000;
int conn[21][21];  //连线矩阵
int n;             //元件个数
int bestx[21];     //解向量

class Node {
public:
    int dep;      //当前层
    int val;      //布线费用
    int *x;       //解向量

    Node(int d, int val) {
        x = new int[n + 1];
        dep = d;
    }

    int getVal() //计算当前布线费用
    {
        int cur = 0;
        for(int i = 1; i < dep; i ++) //计算布线成本
        {
            for(int j = i + 1; j <= dep; j ++)
                cur += (conn[i][j] * abs(x[j] - x[i]));
        }
        return cur;
    }

    //布线费用小的先出队列
    bool operator < (const Node &node) const
    {
        return val >= node.val;
    }
};

int search() {
    priority_queue<Node> q;
    Node enode(0, 0);
    for(int j = 1; j <= n; j ++)
        enode.x[j] = j;
    int best = INF;
    while(true) {
        if(enode.dep == n) {
            if(enode.val < best) {
                best = enode.val;
                copy(enode.x, enode.x+n+1, bestx);
                break;
            }
        }
        else {
            for(int i = enode.dep + 1; i <= n; i ++) {
                Node now(enode.dep+1, 0);
                copy(enode.x, enode.x + n + 1, now.x);
                now.x[now.dep] = enode.x[i];
                now.x[i] = enode.x[now.dep];
                now.val = now.getVal();
                if(now.val < best)
                    q.push(now);
            }
        }
        if(q.empty())
            break;
        else {
            enode = q.top();
            q.pop();
        }
    }
    return best;
}

int main() {
    cin >> n;
    for(int i = 1; i < n; i ++)
        for(int j = i + 1; j <= n; j ++)
            cin >> conn[i][j];

    cout << search() << endl;
    for(int i = 1; i <= n; i ++)
        cout << bestx[i] << " ";
    return 0;
}