//
// Created by 86158 on 2023/12/24.
//
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<string>
#include<stack>
#include<queue>
#include<cstring>
#include<memory.h>
#include<map>
#include<iterator>
#include<list>
#include<set>
#include<functional>

using namespace std;

const int maxn=102;
int v[4];//为了简单判断，使这些杯子有规律性，我们编号
struct node{
    int v[4];//表示当前状态的三个杯子里的剩余量。
    int step;//记录步骤
};
node temp,head;
bool visited[maxn][maxn][maxn];//辅助数组，判断某个状态是否已经访问
void pour(int a,int b){
    //第a个杯子往第b个杯子里倒水。
    int sum=temp.v[a]+temp.v[b];//
    if(sum>=v[b]){
        //如果总量大于第b个杯子的容量，则
        temp.v[b]=v[b];
    }
    else{
        //小于则直接等于总容量。
        temp.v[b]=sum;
    }
    //最后第a个杯子剩余的容量。
    temp.v[a]=sum-temp.v[b];
}
void bfs(){
    //我们一定要v[1]>v[2]>=v[3]。
    queue<node> q;
    head.v[1]=v[1];head.v[2]=head.v[3]=head.step=0;
    memset(visited,false,sizeof(visited));
    visited[v[1]][0][0]=true;
    q.push(head);
    while(!q.empty()){
        head=q.front();
        q.pop();
        if(head.v[1]==head.v[2]&&head.v[3]==0){
            cout<<head.step<<endl;
            return;
        }
        for(int i=1;i<4;i++){
            for(int j=1;j<4;j++){
                //模拟倒水情况。
                if(i!=j){
                    //自己肯定不能给自己倒水，故这里排除杯子编号相等的情况。
                    temp=head;
                    pour(i,j);
                    if(!visited[temp.v[1]][temp.v[2]][temp.v[3]]){
                        visited[temp.v[1]][temp.v[2]][temp.v[3]]=true;
                        temp.step++;
                        q.push(temp);
                    }
                }
            }
        }
    }
    cout<<"NO"<<endl;
}
int main() {
    while(cin>>v[1]>>v[2]>>v[3]&&(v[1]+v[2]+v[3])){
        if(v[1]%2){cout<<"NO"<<endl;continue;}//判断是否为奇数。
        if(v[2]<v[3]){
            //为了保证我们这个规律：v[1]>v[2]>=v[3]。
            int t=v[3];
            v[3]=v[2];
            v[2]=t;
        }
        bfs();
    }
    return 0;
}

