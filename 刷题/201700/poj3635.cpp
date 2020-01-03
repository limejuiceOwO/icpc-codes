#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 1005
#define C 105
using namespace std;

struct Node {
  int d,u,fuel;
  bool operator <(const Node &rhs) const{
    return d>rhs.d;
  }
};

struct Edge {
  int u,v,w;
};

vector<Edge> G[N];
int d[N][C],price[N];
int n,cap;

void djst(int st)
{
    priority_queue<Node> pq;
    memset(d,0x7f,sizeof(d));
    d[st][0]=0;
    pq.push((Node){0,st,0});
    while(!pq.empty()) {
        Node cur=pq.top();pq.pop();
        int u=cur.u,fuel=cur.fuel;
        if(cur.d>d[u][fuel]) continue;
        if(fuel<cap&&d[u][fuel]+price[u]<d[u][fuel+1]) {
          d[u][fuel+1]=d[u][fuel]+price[u];
          pq.push((Node){d[u][fuel+1],u,fuel+1});
        }
        for(int i=0;i<G[u].size();i++) {
            int v=G[u][i].v,w=G[u][i].w;
            if(fuel>=w&&d[u][fuel]<d[v][fuel-w]) {
                d[v][fuel-w]=d[u][fuel];
                pq.push((Node){d[v][fuel-w],v,fuel-w});
            }
        }
    }
}

int main()
{
  //freopen("poj3635.txt","r",stdin);
  cin.sync_with_stdio(false);
  int m;
  cin>>n>>m;
  for(int i=0;i<n;i++) {
    cin>>price[i];
  }
  for(int i=0;i<m;i++) {
    Edge e;
    cin>>e.u>>e.v>>e.w;
    G[e.u].push_back(e);
    swap(e.u,e.v);
    G[e.u].push_back(e);
  }
  int Q;
  cin>>Q;
  while(Q--) {
    int st,ed;
    cin>>cap>>st>>ed;
    djst(st);
    int mincost=1000000;
    for(int i=0;i<=cap;i++) {
      mincost=min(mincost,d[ed][i]);
    }
    if(mincost==1000000) {
      cout<<"impossible"<<endl;
    } else {
      cout<<mincost<<endl;  
    }
  }
  return 0;
}
