#include<bits/stdc++.h>
#define N 100000
using namespace std;

vector<int> edges[N];
long long bit[N+1],bit2[N+1];
int dep[N],top[N],pos[N],wson[N],fa[N],rnk[N];
int tsize,n;

inline long long _lookup(long long *tr,int idx)
{
  long long ans=0;
  while(idx&&idx<=n) {
    ans+=tr[idx];
    idx-=(idx&-idx);
  }
  return ans;
}

inline void _alter(long long *tr,int idx,long long delta)
{
  while(idx&&idx<=n) {
    tr[idx]+=delta;
    idx+=(idx&-idx);
  }
}

inline void alter(int a,int b,long long delta)
{
  _alter(bit,a,delta);
  _alter(bit2,a,a*delta);
  _alter(bit,b+1,-delta);
  _alter(bit2,b+1,-(b+1)*delta);
}

inline long long lookup(int a,int b)
{
  return (b+1)*_lookup(bit,b)-_lookup(bit2,b)-(a*_lookup(bit,a-1)-_lookup(bit2,a-1));
}

void dfs1(int u)
{
  rnk[u]=1;
  wson[u]=-1;
  for(unsigned int i=0;i<edges[u].size();i++) {
    int v=edges[u][i];
    if(fa[u]==v) continue;
    fa[v]=u;
    dep[v]=dep[u]+1;
    dfs1(v);
    rnk[u]+=rnk[v];
    if(wson[u]<0||rnk[wson[u]]<rnk[v])   wson[u]=v;
  }
}

void dfs2(int u)
{
  pos[u]=++tsize;
  if(wson[u]>0) {
    top[wson[u]]=top[u];
    dfs2(wson[u]);
  }
  for(unsigned int i=0;i<edges[u].size();i++) {
    int v=edges[u][i];
    if(fa[u]==v||v==wson[u]) continue;
    top[v]=v;
    dfs2(v);
  }
}

long long query(int u,int v)
{
  int f1=u,f2=v;
  long long ans=0;
  while(top[f1]!=top[f2]) {
    if(dep[top[f1]]<dep[top[f2]]) swap(f1,f2);//top×¢Òâ 
    ans+=lookup(pos[top[f1]],pos[f1]);
    f1=fa[top[f1]];
  }
  if(dep[f1]>dep[f2]) swap(f1,f2);;
  ans+=lookup(pos[f1],pos[f2]);
  return ans;
}

void change(int u,int v)
{
  int f1=u,f2=v;
  while(top[f1]!=top[f2]) {
    if(dep[top[f1]]<dep[top[f2]]) swap(f1,f2);
    alter(pos[top[f1]],pos[f1],1);
    f1=fa[top[f1]];
  }
  if(dep[f1]>dep[f2]) swap(f1,f2);
  alter(pos[f1],pos[f2],1);
}

int main()
{
  cin.sync_with_stdio(false);
  int m;
  cin>>n;
  for(int i=1,u,v;i<n;i++) {
    cin>>u>>v;
    u--;v--;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs1(0);
  dfs2(0);
  cin>>m;
  while(m--) {
    int c,u,v;
    cin>>c>>u>>v;
    u--;v--;
    if(c==2) {
      cout<<query(u,v)<<endl;
    } else {
      change(u,v);
    }
  }
  return 0;
}
