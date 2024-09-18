//
// Created by Lenovo on 2023/12/18.
//
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int MAX = 1000;
int G[MAX][MAX];//存储边信息
int bestx[MAX];//最优值的割集
int w[MAX];//顶点的权
int n, e; //顶点数，边数

//结点类
class Node {
public:
    int dep;  //当前层
    int cut;  //割边数量
    int e;    //剩余边的数量
    int *x;   //解向量

    Node(int d, int c, int ee) {
        x = new int[n+1];
        dep = d;
        cut = c;
        e = ee;
    }

    //割边数大的先出队列
    bool operator < (const Node &node) const {
        return cut < node.cut;
    }
};

//存储待解决的结点的优先队列
priority_queue<Node> q;

//添加结点
void addNode(Node enode, bool isLeft) {
    Node now(enode.dep+1, enode.cut, enode.e);
    copy(enode.x, enode.x+n+1, now.x);
    //是左结点
    if(isLeft)
    {
        now.x[now.dep] = 1;//标记是割集元素
        for(int j = 1; j <= n; j ++)//统计割边的增量
            if(G[now.dep][j])
                if(now.x[j] == 0) //如果当前顶点在割集中，但边的另一个顶点不在割集
                {
                    now.cut ++;  //割边的数量增加
                    now.e --;    //剩余边的数量减少
                }
                else now.cut --;//否则割边数量减少
    }
    q.push(now);//加入优先队列
}

int search() {
    //初始化
    Node enode(0, 0, e);
    for(int j = 1; j <= n; j ++)
        enode.x[j] = 0;
    int best = 0;
    //分支限界求解
    while(true) {
        if(enode.dep>n)//到达叶子节点，如果比当前最优解更优，更新
        {
            if(enode.cut > best) {
                best = enode.cut;
                copy(enode.x, enode.x + n + 1, bestx);
                break;
            }
        }
        else//没有到达叶子节点
        {
            addNode(enode, true);//加入左子结点
            if(enode.cut + enode.e > best)//满足约束条件，加入右子结点
                addNode(enode, false);
        }
        if(q.empty())
            break;
        else//取出队首元素
        {
            enode = q.top();
            q.pop();
        }
    }
    return best;
}

int main() {
    int a, b;
    cin >> n >> e;
    memset(G, 0, sizeof(G));
    for(int i = 1; i <= e; i ++) {
        cin >> a >> b;
        G[a][b] = G[b][a] = 1;
    }
    cout << search()<<'\n';
    for(int i = 1; i <= n; i ++){
        cout << bestx[i];
        if(i != n) cout << " ";
    }
    cout << '\n';

    return 0;
}

/*测试数据：
7 18
1 4
1 5
1 6
1 7
2 3
2 4
2 5
2 6
2 7
3 4
3 5
3 6
3 7
4 5
4 6
5 6
5 7
6 7

结果：
12
1 1 1 0 1 0 0
*/