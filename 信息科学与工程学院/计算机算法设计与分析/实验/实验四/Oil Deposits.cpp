//
// Created by 86158 on 2023/12/24.
//
# include <cstdio>
using namespace std;
char abc[120][120];
int a[8]={-1,-1,0,1,1,1,0,-1};
int b[8]={0,1,1,1,0,-1,-1,-1};
void dfs(int x,int y)
{
    int k;
    if(x<0 || y<0)
        return;     //这里的return返回很重要！！回溯
    if(abc[x][y]=='@')
    {
        abc[x][y]='*';
        for(k=0;k<8;k++)
            dfs(x+a[k],y+b[k]);  //等同int dx=x+vis[i][0]; //int dy=y+vis[i][1];
    }
    return;
}
int main()
{
    int m,n;
    while(scanf("%d%d",&m,&n)!=EOF&&(m||n))
    {
        int i,j;
        int ans=0;
        for(i=0;i<m;i++)
            scanf("%s",abc[i]);
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(abc[i][j]=='@')
                {
                    ans++;
                    dfs(i,j);
                }
            }
        }

        printf("%d\n",ans);

    }
    return 0;
}