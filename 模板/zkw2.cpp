//zkw线段树 差分版 单点查询+区间修改
#include <iostream>
#include <algorithm>
#define K 10
const int N=2*(1<<K)+10;
using namespace std;

int tree[N];
int n;

int qur(int idx) //sum[l,r] 
{
  int ans=0;
  for(idx+=n;idx;idx>>=1) ans+=tree[idx];
  return ans;
}

void alter(int l,int r,int delta)
{
  for(l+=n-1,r+=n+1;(l^r)^1;l>>=1,r>>=1) {
    if(!(l&1)) tree[l^1]+=delta; 
    if(r&1) tree[r^1]+=delta;
  }
}

void build()
{
  for(int i=n-2;i;i--) {
    tree[i]=tree[i<<1]+tree[(i<<1)|1]; 
    tree[i<<1]-=tree[i];
    tree[i<<1|1]-=tree[i];
  }
}

int main()
{
  int nn;
  cin>>nn;
  nn+=2;
  for(n=1;n<nn;n<<=1);
  for(int i=1;i<=nn-2;i++) { 
    cin>>tree[i+n];
  }
  build();
  while(1) {
    int c,l,r,v;
    cin>>c;
    if(c==1) {
      cin>>l;
      cout<<qur(l)<<endl;
    } else {
      cin>>l>>r>>v;
      alter(l,r,v);
    }
  }
  return 0;
}
