#include<bits/stdc++.h>
using namespace std;
#define pill pair<int,int>
#define inf 0x3f3f3f3f

int dis[5001][5001];

int match[5001],lx[5001],ly[5001],slack[5001];//ËÉ³Ú¶È
bool visx[5001],visy[5001];

int dfs(int u,int m){
    visx[u]=1;
    for(int i=1;i<=m;i++){
        if(visy[i])continue;
        int t=lx[u]+ly[i]-dis[u][i];
        if(t==0){
            visy[i]=1;
            if(!match[i]||dfs(match[i],m)){
                match[i]=u;
                return 1;
            }
        }
        else if(slack[i]>t){
            slack[i]=t;//À­½ô
        }
    }
    return 0;
}

int KM(int n,int m){
    memset(match,0,sizeof(match));
    memset(ly,0,sizeof(ly));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            lx[i]=max(lx[i],dis[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)slack[j]=inf;
        while(1){
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i,m))break;
            int d=inf;
            for(int j=1;j<=m;j++){
                if(!visy[j])d=min(d,slack[j]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j])lx[j]-=d;
            }
            for(int j=1;j<=m;j++){
                if(visy[j])ly[j]+=d;
                else slack[j]-=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        if(match[i])ans+=dis[match[i]][i];
    }
    return ans;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)){
        //init dis[][]
        int ans=KM(n,m);
    }
}

