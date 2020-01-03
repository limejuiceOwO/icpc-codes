#include <bits/stdc++.h>
#define N 10005
using namespace std;
typedef pair<int,int> PI;

int d[N];
vector<PI> G[N];

void djst(int st)
{
    priority_queue<PI,vector<PI>,greater<PI> > pq;
    //fill(d,d+N,1000000);
    memset(d,0x7f,N*sizeof(int));
    d[st]=0;
    pq.push(make_pair(0,st));
    while(!pq.empty()) {
        PI cur=pq.top();pq.pop();
        int u=cur.second;
        if(cur.first>d[u]) continue;
        for(int i=0;i<G[u].size();i++) {
            int v=G[u][i].first,dist=G[u][i].second;
            if(d[u]+dist<d[v]) {
                d[v]=d[u]+dist;
                pq.push(make_pair(d[v],v));
            }
        }
    }
} 

int main()
{
    freopen("spfa.txt","r",stdin);
    cin.sync_with_stdio(false);
    int n,m,st,ed;
    cin>>n>>m>>st>>ed;
    for(int i=0;i<m;i++) {
        int u,v,d;
        cin>>u>>v>>d;
        G[u].push_back(make_pair(v,d));
        G[v].push_back(make_pair(u,d));
    }
    djst(st);
    cout<<d[ed]<<endl;
    return 0;
}
