#include <iostream>
#include <queue>
#include <cstring>
#define N 1000
#define M 200
using namespace std;
typedef pair<int,int> PI;

int d[N],fa[N];
vector<PI> G[N];
int n,m;

void djst(int st)
{
  priority_queue<PI,vector<PI>,greater<PI> > pq;
  memset(d,0x7f,sizeof(d));
  d[st]=0;
  pq.push(make_pair(0,st));
  while(!pq.empty()) {
    PI cur=pq.top();pq.pop();
    int u=cur.second;
    if(cur.first>d[u]) continue;
    for(unsigned int i=0;i<G[u].size();i++) {
      int v=G[u][i].first,dist=G[u][i].second;
      if(d[u]+dist<d[v]) {
        d[v]=d[u]+dist;
        fa[v]=u;
        pq.push(make_pair(d[v],v));
      }
    }
  }
}


int main()
{
  int st;
  cin >> n >> m >> st;
  for(int i=0;i<m;i++) {
    int u,v,d;
    cin >> u >> v >> d;
    G[u].push_back(make_pair(v,d));
    //G[v].push_back(make_pair(u,d));
  }
  djst(st);
  for(int i=0;i<n;i++)
    printf("%d:%d\n",i,d[i]);
  return 0;
}

