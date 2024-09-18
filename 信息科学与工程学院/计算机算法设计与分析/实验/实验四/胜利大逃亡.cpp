//
// Created by 86158 on 2023/12/24.
//
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int Maze[51][51][51];			//存储迷宫
int vis[51][51][51];			//存储该状态是否来过了
int dir[6][3] = {{1,0,0},{0,0,1},{-1,0,0},{0,0,-1},{0,1,0},{0,-1,0}};		//状态转移数组
int A, B, C, time;

struct node
{
    int x,y,z;
    int step;
};

void BFS(){
    memset(vis,0,sizeof(vis));
    node Now,next;
    Now.x = Now.y = Now.z = Now.step = 0;
    vis[0][0][0] = 1;

    queue<node> q;

    q.push(Now);

    while (!q.empty()) {
        Now = q.front();
        q.pop();

        if(Now.x == A - 1&& Now.y == B - 1 && Now.z == C - 1)
        {
            if (Now.step <= time)
            {cout << Now.step << endl;
                return ;}
            else{
                cout << -1 << endl;
                return ;
            }
        }
        for(int i = 0;i < 6; i++){
            next.x = Now.x + dir[i][0];
            next.y = Now.y + dir[i][1];
            next.z = Now.z + dir[i][2];
            if (next.x>=0&&next.x <= A - 1&&next.y>=0&&next.y <= B - 1&&next.z >= 0 && next.z <= C - 1 &&Maze[next.x][next.y][next.z] != 1&&!vis[next.x][next.y][next.z])
            {
                next.step = Now.step + 1;
                vis[next.x][next.y][next.z] = 1;
                q.push(next);
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> A >> B >> C >> time;
        for(int i = 0;i < A;i++){
            for(int j = 0; j < B; j++){
                for(int k = 0; k < C; k++) {
                    scanf("%d",&Maze[i][j][k]);
                }
            }
        }
        BFS();
    }
}


