#include <bits/stdc++.h>
#define M 16
using namespace std;
const int N=(1<<M)+10;


int anc[N][M+1],dep[N];
vector<int> G[N];

void build(int u,int fa)
{
    for(unsigned int i=0;i<G[u].size();i++) {
        int v=G[u][i];
        if(v==fa) continue;
        dep[v]=dep[u]+1;
        anc[v][0]=u;
        for(int k=1;k<=M;k++) {
            anc[v][k]=anc[anc[v][k-1]][k-1];
        }
        build(v,u);
    }
}

int query(int a,int b)
{
    int u1=a,u2=b;
    if(dep[u1]<dep[u2]) swap(u1,u2);
    for(int k=M;k>=0&&dep[u1]>dep[u2];k--) {
        if(dep[anc[u1][k]]>=dep[u2]) {
            u1=anc[u1][k];
        }
    }
    if(u1==u2) return u1;
    for(int k=M;k>=0;k--) {
        if(anc[u1][k]!=anc[u2][k]) {
            u1=anc[u1][k];
            u2=anc[u2][k];
        }
    }
    return anc[u1][0];
}

int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    fill(anc[1],anc[1]+M,1);
    build(1,-1);
    while(m--) {
        int a,b;
        cin>>a>>b;
        cout<<query(a,b)<<endl;
    }
    return 0;
}