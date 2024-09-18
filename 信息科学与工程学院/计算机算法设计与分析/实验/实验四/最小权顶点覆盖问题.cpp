#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 50;
int G[MAX][MAX];
int bestx[MAX];
int w[MAX];     //顶点的权
int n, e; //电路板数，连接块数

class Node {
public:
    int dep;  //当前层
    int val;  //所含顶点权值之和
    int *x;   //解向量
    int *c;   //边上的另一个顶点

    Node() {
        x = new int[n + 1];
        c = new int[n + 1];
    }

    //当前排列长度小的先出队列
    bool operator < (const Node &node) const {
        return val >= node.val;
    }
};

priority_queue<Node> q;

//判断图是否已完全覆盖
bool cover(Node E) {
    for(int i = 1; i <= n; i ++)
        if(E.x[i] == 0 && E.c[i] == 0)
            return false;
    return true;
}

//添加结点
void addNode(Node enode, int i, int v, bool isLeft) {
    Node now;
    now.dep = i;
    copy(enode.x, enode.x + n + 1, now.x);
    copy(enode.c, enode.c + n + 1, now.c);
    if(isLeft) {
        now.val = v + w[i];
        now.x[i] = 1;
        for(int j = 1; j <= n; j ++)
            if(G[j][i])
                now.c[j] ++;
    }
    else {
        now.val = v;
        now.x[i] = 0;
    }
    q.push(now);
}

int search() {
    Node enode;
    for(int j = 1; j <= n; j ++) {
        enode.x[j] = 0;
        enode.c[j] = 0;
    }
    int best;
    int i = 1;
    int val = 0;
    while(true) {
        if(i > n) {
            if(cover(enode)) {
                best = val;
                copy(enode.x, enode.x+n+1, bestx);
                break;
            }
        }
        else {
            if(!cover(enode))
                addNode(enode, i, val, true);
            addNode(enode, i, val, false);
        }
        if(q.empty())
            break;
        else
        {
            enode = q.top();
            q.pop();
            i = enode.dep + 1;
            val = enode.val;
        }
    }
    return best;
}

int main() {
    cin >> n;
    cin  >> e;
    for(int i = 1; i <= n; i ++)
        cin >> w[i];
    int a, b;
    memset(G, 0, sizeof(G));
    for(int i = 1; i <= e; i ++) {
        cin >> a >> b;
        G[a][b] = G[b][a] = 1;
    }

    cout << search() << "\n";
    for(int i = 1; i <= n; i ++)
        cout << bestx[i] << " ";
    return 0;
}
