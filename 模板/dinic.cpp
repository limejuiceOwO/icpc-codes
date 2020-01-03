#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define N 205
#define M 205
#define INF 100000005
using namespace std;

struct Edge {
    int v,flow,max_flow;
} edge[M];
int cnt=0;

vector<int> G[N];
char vis[N];
int lvl[N];

bool bfs(int st,int ed)
{
    queue<int> q;
    memset(lvl,0,sizeof(lvl));
    q.push(st);
    lvl[st]=1;
    while(!q.empty()) {
        int u=q.front();q.pop();
        for(unsigned int i=0;i<G[u].size();i++) {
            int p=G[u][i],v=edge[p].v;
            if(lvl[v]||edge[p].flow>=edge[p].max_flow) continue;
            lvl[v]=lvl[u]+1;
            if(v==ed) return true;
            q.push(v);
        }
    }
    return false;
}

int dfs(int u,int ed,int e=INF)
{
    if(u==ed) return e;
    for(unsigned int i=0;i<G[u].size();i++) {
        int p=G[u][i],v=edge[p].v;
        if(vis[v]||lvl[v]<=lvl[u]||edge[p].flow>=edge[p].max_flow) continue;
        vis[v]=1;
        int ret=dfs(v,ed,min(e,edge[p].max_flow-edge[p].flow));
        if(ret) {
            edge[p].flow+=ret;
            edge[p^1].flow-=ret;
            return ret;
        }
    }
    return 0;
}

int max_flow(int st,int ed)
{
    int ans=0,cur;
    while(1) {
        if(!bfs(st,ed)) break;
        while(1) {
            memset(vis,0,sizeof(vis));
            vis[st]=1;
            if(!(cur=dfs(st,ed))) break;
            ans+=cur;
            if(ans>=INF) break;
        }
    }
    return ans;
}

void add(int u,int v,int f)
{
    edge[cnt]=(Edge){v,0,f};
    edge[cnt^1]=(Edge){u,f,f};
    G[u].push_back(cnt++);
    G[v].push_back(cnt++);
}

int main()
{
    ios::sync_with_stdio(false);
    while(1) {
        int n,m;
        cin>>m>>n;
        if(cin.eof()) break;
        cnt=0;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<m;i++) {
            int u,v,flow;
            cin>>u>>v>>flow;
            add(u,v,flow);
        }
        cout<<max_flow(1,n)<<endl;
    }
    return 0;
}