#include <bits/stdc++.h>
#define N 10005
using namespace std;
typedef pair<int,int> PI;

vector<PI> G[N];
int d[N];
bool vis[N];
int n,m;

void spfa(int st)
{
  queue<int> q;
  //stack<int> q;
  q.push(st);
  memset(d,0x7f,N*sizeof(int));
  d[st]=0;
  vis[st]=true;
  while(!q.empty()) {
    int u=q.front();q.pop();
    vis[u]=false;
    for(int i=0;i<G[u].size();i++) {
      int v=G[u][i].first,dist=G[u][i].second;
      if(d[u]+dist<d[v]) {
        d[v]=d[u]+dist;
        if(!vis[v]) {
          q.push(v);
          vis[v]=true;
        }
      }
    }
  }
}

int main()
{
    freopen("spfa.txt","r",stdin);
    cin.sync_with_stdio(false);
    int st,ed;
    cin>>n>>m>>st>>ed;
    for(int i=0;i<m;i++) {
        int u,v,d;
        cin>>u>>v>>d;
        G[u].push_back(make_pair(v,d));
        G[v].push_back(make_pair(u,d));
    }
    spfa(st);
    cout<<d[ed]<<endl;
    return 0;
}
