//
// Created by 86158 on 2023/12/24.
//
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
using namespace std;
const int maxn=202;
char mp[maxn][maxn];
bool vis[maxn][maxn];
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
int sx,sy,ex,ey;
int n,m;

struct Node
{
    int x,y;
    int step;
};
int step[maxn][maxn];

bool operator<(Node a,Node b)
{
    return a.step>b.step;
}

bool ok(int x,int y)
{
    if(x>=1&&x<=n&&y>=1&&y<=m&&mp[x][y]!='#')
        return true;
    return false;
}

void BFS(int x,int y)
{
    step[x][y]=0;
    memset(vis,0,sizeof(vis));
    vis[x][y]=1;
    priority_queue<Node>q;
    Node tp;
    tp.x=x,tp.y=y,tp.step=0;
    q.push(tp);
    while(!q.empty())
    {
        Node first=q.top();
        if(first.x==ex&&first.y==ey)
            break;
        q.pop();
        for(int i=0;i<4;i++)
        {
            int nextx=first.x+dx[i];
            int nexty=first.y+dy[i];
            if(!vis[nextx][nexty]&&ok(nextx,nexty))
            {
                vis[nextx][nexty]=1;
                tp.x=nextx;
                tp.y=nexty;
                if(mp[nextx][nexty]=='x')
                {
                    step[nextx][nexty]=first.step+2;
                    tp.step=first.step+2;
                }
                else
                {
                    step[nextx][nexty]=first.step+1;
                    tp.step=first.step+1;
                }
                q.push(tp);
            }
        }
    }
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                cin>>mp[i][j];
                if(mp[i][j]=='r')
                    sx=i,sy=j;
                else if(mp[i][j]=='a')
                    ex=i,ey=j;
            }
        BFS(sx,sy);
        if(!vis[ex][ey])
            printf("Poor ANGEL has to stay in the prison all his life.\n");
        else
            printf("%d\n",step[ex][ey]);
    }
    return 0;
}