#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const int INF = 100000;
const int MAX = 50;
int n, k;         //任务数，机器数
int time[MAX];    //完成任务需要时间

class Node {
public:
    int dep;      //当前层
    int time;     //完成当前任务的时间
    int *machine; //各机器完成任务后的时间

    Node(int d, int t) {
        machine = new int[k + 1];
        dep = d;
        time = t;
    }

    int getTime() //计算完成当前任务需要的时间
    {
        int t = machine[1];
        for(int i = 2; i <= k; i ++)
            if(t < machine[i])
                t = machine[i];
        return t;
    }

    //完成任务时间小的先出队列
    bool operator < (const Node &node) const {
        return time >= node.time;
    }
};

int search() {
    priority_queue<Node> q;
    Node enode(0, 0);
    for(int j = 1; j <= k; j ++)
        enode.machine[j] = 0;
    int best = INF;
    while(true) {
        if(enode.dep == n) {
            if(enode.time < best) {
                best = enode.time;
                break;
            }
        }
        else {
            for(int i = 1; i <= k; i ++) {
                Node now(enode.dep+1, 0);
                copy(enode.machine, enode.machine+k+1, now.machine);
                now.machine[i] += time[now.dep];
                now.time = now.getTime();
                if(now.time < best)
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
    cin >> n >> k;
    for(int i = 1; i <= n; i ++)
        cin >> time[i];
    cout << search() << endl;
    return 0;
}
