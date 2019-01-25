#include<stdio.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
#define LL long long

const int inf=0x3f3f3f3f;
const LL infll=1e18;
const int N=40500,M=405000;

int head[N],nex[M],to[M],val[M],now;
void add(int a,int b,int v){
    to[++now]=b;val[now]=v;nex[now]=head[a];head[a]=now;
    to[++now]=a;val[now]=0;nex[now]=head[b];head[b]=now;
}

//*********************

int sp,ep,d[N];

int bfs(){
    queue<int>Q;
    memset(d,-1,sizeof(d));
    d[sp]=0;
    Q.push(sp);
    while(!Q.empty()){
        int p=Q.front();Q.pop();
        for(int i=head[p];~i;i=nex[i]){
            int u=to[i];
            if(d[u]==-1&&val[i]>0){
                d[u]=d[p]+1;
                Q.push(u);
            }
        }
    }
    return d[ep]!=-1;
}

int dfs(int p,int v){
    int r=0;
    if(p==ep)return v;
    for(int i=head[p];(~i)&&r<v;i=nex[i]){
        int u=to[i];
        if(val[i]>0&&d[u]==d[p]+1){
            int x=dfs(u,min(val[i],v-r));
            r+=x;
            val[i]-=x;
            val[i^1]+=x;
        }
    }
    if(!r)d[p]=-2;
    return r;
}

LL dinic(){//求最大流
    LL ans=0,t;
    while(bfs()){
        while(t=(LL)dfs(sp,inf))ans+=t;
    }
    return ans;
}

//***********************

bool viss[N];
int num;
int count(int p){//遍历残余网络
    int ans=1;
    viss[p]=1;
    for(int i=head[p];~i;i=nex[i]){
        int u=to[i];
        if(viss[u]||val[i]<=0)continue;
        ans+=count(u);
    }
    return ans;
}

//***********************

void init(){
    now=-1;//要求第一条边为0
    memset(head,-1,sizeof(head));
}

int main(){
    init();
    sp=0;ep=N-1;
    ...
    int ans=dinic();
}
