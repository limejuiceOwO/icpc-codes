#include<bits/stdc++.h>
#define P 16
using namespace std;
const int N=(1<<P)+10;

struct Seg {
  int l,r;
  long long val,lazy;
} tree[N];

void build(int l,int r,int p)
{
  tree[p].l=l;
  tree[p].r=r;
  if(l+1==r) cin>>tree[p].val;
  else {
    int mid=l+(r-l)>>1;
    build(l,mid,p*2+1);
    build(mid,r,p*2+2);
    tree[p].val=tree[p*2+1].val+tree[p*2+2].val;
  }
}

void eval(int p)
{
  int &lz=tree[p].lazy;
  if(lz) {
    tree[p*2+1].lazy=tree[p*2+2].lazy=lz;
    tree[p].val+=lz*(r-l);
    lz=0;
  }
}

void alter(int l,int r,int v,int p)
{
  if(l<=tree[p].l&&r>=tree[p].r) {
    tree[p].lazy+=v;
  } else if(l>=tree[p].r||r<=tree[p].l) {
    return;
  } else {
    int mid=l+(r-l)>>1;
    alter(l,mid,v,p*2+1);
    alter(mid,r,v,p*2+2);
  }
}

long long query(int l,int r,int p)
{
  eval(p);
  if(l<=tree[p].l&&r>=tree[p].r) {
    return tree[p].val;
  } else if(l>=tree[p].r||r<=tree[p].l) {
    return;
  } else {
    int mid=l+(r-l)>>1;
    return query(l,mid,v,p*2+1)+query(mid,r,v,p*2+2);
  }
}

int main()
{
  int n;
  cin>>n;
  build(0,n,0);
  while(1) {
    int cmd,l,r,v;
    cin>>cmd;
    if(cmd==1) {
      cin>>l>>r;
      cout<<query(l,r,0)<<endl;
    } else {
      cin>>l>>r>>v;
      alter(l,r,v,0);
    }
  }
  return 0;
}
