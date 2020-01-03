#include<bits/stdc++.h>
#define INF 1000000
using namespace std;
long long tree[1000];
int n;

long long lookup(int a,int b,int p,int l,int r)
{
  if(b<l||a>r) return -INF;
  else if(l>=a&&r<=b) return tree[p];
  else {
    int mid=l+((r-l)>>1);
    return max(lookup(a,b,p*2+1,l,mid),lookup(a,b,p*2+2,mid+1,r));
  }
}

void alter(int idx,long long val)
{
  idx+=n-1;
  tree[idx]=val;
  while(idx>0) {
    idx=(idx-1)>>1;
    tree[idx]=max(tree[idx*2+1],tree[idx*2+2]);
  }
}

int main()
{
  cin>>n;
  fill(tree,tree+1000,-INF);
  int nn=1;
  while(nn<n) nn<<=1;
  n=nn;
  while(1) {
    int c,a,b;
    cin>>c>>a>>b;
    if(c==1) {
      cout<<lookup(a,b,0,0,n-1)<<endl;
    } else {
      alter(a,b);
    }
  }
  return 0;
}
