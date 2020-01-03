#include<bits/stdc++.h>
#define N 16384
#define INF 1000000
using namespace std;

struct Edge {
  int u,v,d;
} edges[2*N];
int tree[2*N];
int dep[N],top[N],pos[N],wson[N],wdist[N],fa[N],rnk[N],first[N],nxt[N];
int esize,tsize,n;

inline void push(Edge e)
{
  edges[esize]=e;
  nxt[esize]=first[e.u];
  first[e.u]=esize++;
}

int lookup(int a,int b,int p,int l,int r)
{
  if(b<l||a>r) return -INF;
  else if(l>=a&&r<=b) return tree[p];
  else {
    int mid=l+((r-l)>>1);
    return max(lookup(a,b,p*2+1,l,mid),lookup(a,b,p*2+2,mid+1,r));
  }
}

void alter(int idx,int val)
{
  idx+=n-1;
  tree[idx]=val;
  while(idx>0) {
    idx=(idx-1)>>1;
    tree[idx]=max(tree[idx*2+1],tree[idx*2+2]);
  }
}

void dfs1(int u) //求出rnk,wson,wdist,dep,fa
{
  rnk[u]=1;
  wson[u]=-1;
  for(int i=first[u];i>=0;i=nxt[i]) {
    int v=edges[i].v;
    if(v==fa[u]) continue;
    fa[v]=u;
    dep[v]=dep[u]+1;
    dfs1(v);
    rnk[u]+=rnk[v];
    if(wson[u]<0||rnk[wson[u]]<rnk[v]) {
      wson[u]=v;
      wdist[u]=edges[i].d;
    }
  }
}

void dfs2(int u) //求出pos,top并将边压入线段树 
{
  if(wson[u]>0) {
    top[wson[u]]=top[u];
    pos[wson[u]]=tsize;
    alter(tsize++,wdist[u]);
    dfs2(wson[u]);
  }
  for(int i=first[u];i>=0;i=nxt[i]) {
    int v=edges[i].v;
    if(v==fa[u]||v==wson[u]) continue;
    top[v]=v;
    pos[v]=tsize;
    alter(tsize++,edges[i].d);
    dfs2(v);
  }
}

int query(int u,int v)
{
  int ans=-INF,f1=u,f2=v;
  while(top[f1]!=top[f2]) {
    if(dep[top[f1]]<dep[top[f2]]) swap(f1,f2);//注意是top[f1],不是f1
    ans=max(ans,lookup(pos[top[f1]],pos[f1],0,0,n-1));
    f1=fa[top[f1]];
  }
  if(f1!=f2) {
    if(dep[f1]>dep[f2]) swap(f1,f2);
    ans=max(ans,lookup(pos[wson[f1]],pos[f2],0,0,n-1));
  }
  return ans;
}

int main()
{
  //cin.sync_with_stdio(false);
  freopen("spoj375.txt","r",stdin);
  int t;
  char cmd[20];
  cin>>t;
  while(t--) {
    cin>>n;
    esize=tsize=0;
    fill(first,first+n,-1);
    for(int i=1;i<n;i++) {
      Edge e;
      cin>>e.u>>e.v>>e.d;
      e.u--;e.v--;
      push(e);
      swap(e.u,e.v);
      push(e);
    }
    int nn=1;
    while(nn<n) nn<<=1;
    n=nn;
    fill(tree,tree+2*n,-INF);
    dfs1(0);
    dfs2(0);
    cin>>cmd;
    while(cmd[0]!='D') {
      int u,v;
      cin>>u>>v;
      u--;v--;
      if(cmd[0]=='Q') {
        cout<<query(u,v)<<endl;
      } else {
        alter(fa[edges[u].u]==edges[u].v?pos[edges[u].u]:pos[edges[u].v],v+1);
      }
      cin>>cmd;
    }
  }
  return 0;
}
