//
// Created by 86158 on 2023/12/24.
//
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int main(){
    int n,m;
    vector<float> w(10001,0),v(10001,0);
    vector<float> dp(10001,1);//二维则超出限制内存
    while(cin>>n>>m){
        if(n==0&&m==0) break;
        for(int i=1;i<=m;i++) scanf("%f %f",&w[i],&v[i]);
        for(int j=0;j<=n;j++) dp[j]=1;
        for(int i=1;i<=m;i++){
            for(int j=n;j>=w[i];j--){
                dp[j]=min(dp[j],dp[j-w[i]]*(1-v[i]));
            }
        }
        printf("%.1f%%\n",(1-dp[n])*100);
    }
}