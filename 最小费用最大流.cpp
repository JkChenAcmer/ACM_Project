#include<stdio.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
#define LL long long
#define pill pair<int,int>
#define debug(i) printf("# %d\n",i)

const int inf=0x3f3f3f3f;
const LL infll=1e18;
const int N=110,M=20202;

int head[N],nex[M],to[M],val[M],cost[M],now;
void add(int a,int b,int v,int c){
    to[++now]=b;val[now]=v;cost[now]=c;nex[now]=head[a];head[a]=now;
    to[++now]=a;val[now]=0;cost[now]=-c;nex[now]=head[b];head[b]=now;
}

//*********************

int sp,ep,dis[N];

bool vis[N];
int pre[N];

bool SPFA(int &flow,int &cos){
    memset(vis,0,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    for(int i=0;i<N;i++)dis[i]=inf;

    queue<int>Q;
    dis[sp]=0;vis[sp]=1;Q.push(sp);
    int d=inf;
    while(!Q.empty()){
        int p=Q.front();Q.pop();
        vis[p]=0;
        for(int i=head[p];~i;i=nex[i]){
            int u=to[i];
            if(val[i]>0&&dis[u]-cost[i]>dis[p]){
                dis[u]=dis[p]+cost[i];
                pre[u]=i;
                if(!vis[u]){
                    vis[u]=1;Q.push(u);
                }
            }
        }
    }
    if(dis[ep]==inf)return 0;
    for(int i=pre[ep];~i;i=pre[to[i^1]]){
        d=min(d,val[i]);
    }
    for(int i=pre[ep];~i;i=pre[to[i^1]]){
        val[i]-=d;
        val[i^1]+=d;
        cos+=cost[i]*d;
    }
    flow+=d;
    return 1;
}

pill MinCost(){
    int flow=0,cost=0;
    while(SPFA(flow,cost)){}
    return {flow,cost};
}

//***********************

void init(){
    now=-1;//要求第一条边为0
    memset(head,-1,sizeof(head));
}

int main(){int ca=0;int t;cin>>t;while(t--){
    init();
    sp=0,ep=N-1;
    ...
    pill ans=MinCost();//{flow , cost}
}}
