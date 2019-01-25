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

int in[N],out[N],sum;

void init(){
    now=-1;//要求第一条边为0
    memset(head,-1,sizeof(head));
    sum=0;
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
}

//建反悔图，流过一条反悔删除边，相当于保留
int main(){int ca=0;int t;cin>>t;while(t--){
    init();
    sp=0,ep=N-1;
    int n,m,_sp,_ep;scanf("%d%d%d%d",&n,&m,&_sp,&_ep);
    in[_sp]++,out[_ep]++;//统一所有点：in==out

    for(int i=1;i<=m;i++){
        int a,b,v_stay,v_cut;
        scanf("%d%d%d%d",&a,&b,&v_stay,&v_cut);
        if(v_stay>v_cut){//添 用以反悔删除的边
            add(a,b,1,v_stay-v_cut);
            sum+=v_cut;//默认先删除
        }
        else{//添 反悔连接的边
            add(b,a,1,-v_stay+v_cut);//反向：因为这样反悔后in[a]++,out[b]++ 相当于out[a]--,in[b]--
            sum+=v_stay;
            out[a]++,in[b]++;//默认先连接
        }
    }
    //将还需要配对的度连入
    int sum_in=0;
    for(int i=1;i<=n;i++){
        if(in[i]>out[i])add(sp,i,in[i]-out[i],0),sum_in+=in[i]-out[i];
        else add(i,ep,out[i]-in[i],0);
    }

    pill ans=MinCost();
    if(ans.first!=sum_in)printf("Case %d: impossible\n",++ca);
    else printf("Case %d: %d\n",++ca,ans.second+sum);
}}
