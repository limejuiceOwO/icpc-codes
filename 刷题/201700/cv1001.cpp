#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef pair<double,int> pii ;

const int MAXN=50,INF=1000000;
struct Edge {
  int u,v,d;
};
vector<Edge> adj[MAXN];
int maxd[MAXN],mind[MAXN];
int m,n;

int gcd(int a,int b)
{
  return b==0?a:gcd(b,a%b);
}

void dijkstra(int s)
{
  priority_queue<pii,vector<pii>,greater<pii>> pq;
  fill(maxd,maxd+n,0);
  fill(mind,mind+n,INF);
  maxd[s]=mind[s]=1;
  pq.push(make_pair(1,s));
  while(!pq.empty()) {
    pii p=pq.top();pq.pop();
    int u=p.second;
    if(p.first>(double)maxd[u]/mind[u]) continue;
    for(int i=0;i<adj[u].size();i++) {
      Edge e=adj[u][i];
      int nmaxd=max(maxd[u],e.d);
      int nmind=min(mind[u],e.d);
      if(maxd[e.v]<1||(double)nmaxd/nmind<(double)maxd[e.v]/mind[e.v]) {
        maxd[e.v]=nmaxd;
        mind[e.v]=nmind;
        pq.push(make_pair((double)nmaxd/nmind,e.v));
      }
    }
  }
}

int main()
{
  int s,t;
  cin>>n>>m;
  for(int i=0;i<m;i++) {
    int u,v,d;
    cin>>u>>v>>d;
    adj[u].push_back((Edge){u,v,d});
  }
  cin>>s>>t;
  dijkstra(s);
  cout<<maxd[t]<<" "<<mind[t]<<endl;
  /*
  if(maxd[t]%mind[t]) {
    int g=gcd(maxd[t],mind[t]);
    cout<<maxd[t]/g<<"/"<<mind[t]/g<<endl;
  } else {
    cout<<maxd[t]/mind[t]<<endl;
  }
  */
  return 0;
}
