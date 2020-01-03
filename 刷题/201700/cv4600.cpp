#include<bits/stdc++.h>
#define N 2000010
using namespace std;

pair<int,int> q[N];
int ufs[N];
int qcnt,idcnt;
map<int,int> mp;

int id(int m)
{
  return mp[m]?mp[m]:mp[m]=++idcnt;
}

int find(int u)
{
  return ufs[u]==u?u:ufs[u]=find(ufs[u]);
}

void uni(int a,int b)
{
  if(find(a)==find(b)) return;
  ufs[a]=b;
}

int main()
{
  int t;
  cin>>t;
  while(t--) {
    int n;
    cin>>n;
    for(int i=0;i<2*n;i++) ufs[i]=i;
    for(int i=0;i<n;i++) {
      int cmd,a,b;
      cin>>cmd>>a>>b;
      if(cmd==1) uni(id(a),id(b));
      else q[qcnt++]=make_pair(id(a),id(b));
    }
    int i;
    for(i=0;i<qcnt;i++) {
      if(find(q[i].first)==find(q[i].second)) {
        cout<<"NO"<<endl;
        break;
      }
    }
    if(i==qcnt) cout<<"YES"<<endl;
  }
  return 0;
}
