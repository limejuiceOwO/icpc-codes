#include<bits/stdc++.h>
using namespace std;

int G[100][100];
int mx[100];
bool vis[100];
int m,n;

int prim()
{
  int mst=0;
  fill(mx,mx+n,INF);
  mx[0]=0;
  for(int cnt=0;cnt<n;cnt++) {
    int mr=INF,u;
    for(int i=0;i<n;i++)
      if(!vis[i]&&mx[i]<mr) {
        mr=mx[i];
        u=i;
      }
    mst+=mr;
    vis[u]=true;
    for(int i=0;i<n;i++)
      m[i]=min(mx[i],G[u][i]);
  }
  return mst;
}

int main()
{
  cin>>n>>m;
  fill(G,G+n*n,INF);
  for(int i=0;i<m;i++) {
    int u,v,d;
    cin>>u>>v>>d;
    G[u][v]=G[v][u]=min(G[u][v],d);
  }
  cout<<prim()<<endl;
  return 0;
}
