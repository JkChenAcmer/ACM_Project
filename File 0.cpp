#include<bits/stdc++.h>
using namespace std;

int t;
int Mp[10][5][7];

struct node {
    int i, j, d;
    node() {}
    node(int i, int j, int d): i(i), j(j), d(d) {}
};
vector<node>Ans;

void Copy(int tmp[][7], const int Mp[][7]) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7 && Mp[i][j]; j++) {
            tmp[i][j] = Mp[i][j];
        }
    }
}

void OUT(int tmp[][7]) {
    printf("Map :\n");
    for(int j = 6; j >= 0; j--) {
        for(int i = 0; i < 5; i++) {
            if(tmp[i][j])
                printf("%d", tmp[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

bool Clr(int tmp[][7]) {
    bool res = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            if(tmp[i][j] == 0)
                break;
            if(i < 3) {
                int co = 1;
                for(int k = i + 1; k < 5 && abs(tmp[k][j]) == abs(tmp[i][j]); k++, co++) {}
                if(co > 2) {
                    res = 1;
                    for(int k = 0; k < co; k++) {
                        tmp[i + k][j] = -abs(tmp[i + k][j]);
                    }
                }
            }
            if(j < 5) {
                int co = 1;
                for(int k = j + 1; k < 7 && abs(tmp[i][k]) == abs(tmp[i][j]); k++, co++) {}
                if(co > 2) {
                    res = 1;
                    for(int k = 0; k < co; k++) {
                        tmp[i][j + k] = -abs(tmp[i][j + k]);
                    }
                }
            }
        }
    }
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            tmp[i][j] = max(0, tmp[i][j]);
        }
    }
    return res;
}

void Down(int tmp[][7]) {
    for(int i = 0; i < 5; i++) {
        int top = -1;
        for(int j = 0; j < 7; j++) {
            if(tmp[i][j]) {
                swap(tmp[i][j], tmp[i][++top]);
            }
        }
    }
}

bool Empty(int tmp[][7]) {
    for(int i = 0; i < 5; i++)
        if(tmp[i][0])
            return false;
    return true;
}

void dfs(int tmp[5][7], vector<node> step, const int x, const int y, const int di) {//printf("Dfs step:%d (%d,%d,%d)\n",step,x,y,di);
    if(tmp[x + di][y])
        swap(tmp[x + di][y], tmp[x][y]);
    else {
        swap(tmp[x + di][y], tmp[x][y]);
        tmp[x][y + 1];
        for(int j = y; j + 1 < 7 && tmp[x][j + 1]; j++) {
            swap(tmp[x][j], tmp[x][j + 1]);
        }
        for(int j = y; j - 1 > -1 && !tmp[x + di][j - 1]; j--) {
            swap(tmp[x + di][j], tmp[x + di][j - 1]);
        }
    }
    while(Clr(tmp)) {
        Down(tmp);
        if(Empty(tmp)) {
            if(Ans.size()==0)Ans.assign(step.begin(),step.end());
            else if(step.size() < Ans.size())
                Ans.assign(step.begin(),step.end());
            else if(step.size() == Ans.size()) {
                for(int i=0;i<step.size();i++){
                    if(step[i].i>Ans[i].i)return;
                    if(step[i].i<Ans[i].i){Ans.assign(step.begin(),step.end());return;}
                    if(step[i].j>Ans[i].j)return;
                    if(step[i].j<Ans[i].j){Ans.assign(step.begin(),step.end());return;}
                    if(step[i].d<Ans[i].i)return;
                    if(step[i].i>Ans[i].i){Ans.assign(step.begin(),step.end());return;}
                }
            }
            return ;
        }
    }
    if(step.size() == t)
        return ;
    if(Ans.size() &&step.size() >= Ans.size())
        return;

    for(int i = 0; i < 5; i++) {
        for(int j = 0; tmp[i][j] && j < 7; j++) {
            for(int d = -1; d < 2; d += 2) {
                if(i + d < 0 || i + d > 4 || tmp[i][j]==tmp[i+d][j])
                    continue;
                if(d==-1&&tmp[i+d][j])
                    continue;
                step.push_back(node(i, j, d));
                Copy(Mp[step.size()], tmp);
                dfs(Mp[step.size()], step, i, j, d);
                step.pop_back();
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    for(int i = 0; i < 5; i++) {
        int p = -1, tmp;
        while(scanf("%d", &tmp)) {
            Mp[0][i][++p] = tmp;
            if(!tmp)
                break;
        }
    }
    vector<node>V;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; Mp[0][i][j] && j < 7; j++) {
            for(int d = -1; d < 2; d += 2) {
                if(i + d < 0 || i + d > 4|| Mp[0][i][j]==Mp[0][i+d][j])
                    continue;
                if(d==-1&&Mp[0][i+d][j])
                    continue;
                V.push_back(node(i, j, d));
                Copy(Mp[1], Mp[0]);
                dfs(Mp[1], V, i, j, d);
                V.pop_back();
            }
        }
    }
    if(Ans.size()==0)printf("-1\n");
    else{
        for(int i=0;i<Ans.size();i++){
            printf("%d %d %d\n",Ans[i].i,Ans[i].j,Ans[i].d);
        }
    }
}
