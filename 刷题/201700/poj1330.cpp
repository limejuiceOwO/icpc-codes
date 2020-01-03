#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define N 10005
using namespace std;

vector<int> son[N];
int depth[N],fa[N];

void dfs(int u,int f)
{
  for(int i=0;i<son[u].size();i++) {
    int v=son[u][i];
    if(v==f) continue;
    depth[v]=depth[u]+1;
    dfs(v,u);
  }
}

int main()
{
  cin.sync_with_stdio(false);
  int T;
  cin>>T;
  while(T--) {
    int n;
    cin>>n;
    for(int i=1;i<n;i++) {
      int u,v;
      cin>>u>>v;
      son[u].push_back(v);
      fa[v]=u;
    }
    for(int i=1;i<=n;i++) {
      if(fa[i]==0) {
        dfs(i,-1);
        break;
      }
    }
    int a,b;
    cin>>a>>b;
    if(depth[a]<depth[b]) swap(a,b);
    while(depth[a]>depth[b]) {
      a=fa[a];
    }
    while(a!=b) {
      a=fa[a];
      b=fa[b];
    }
    cout<<a<<endl;
    for(int i=1;i<=n;i++) {
      son[i].clear();
    }
    memset(fa,0,sizeof(fa));
  }
  return 0;
}
