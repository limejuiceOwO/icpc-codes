//zkw线段树 区间查询+单点修改
#include <iostream>
#include <algorithm>
#define K 10
const int N=2*(1<<K)+10; //需要2*n-1+2+1的空间 
using namespace std;

int tree[N];
int n;

int qur(int l,int r) //sum[l,r] 
{
  int ans=0;
  for(l+=n-1,r+=n+1;(l^r)^1;l>>=1,r>>=1) { //自底向上加，l，r是兄弟节点则结束 
    if(!(l&1)) ans+=tree[l^1]; //如果l是父节点的左儿子（末尾是0 ），则计入l的右儿子 
    if(r&1) ans+=tree[r^1]; //如果r是右儿子（末尾是1 ），则计入r的左儿子 
  }
  return ans;
}

void alter(int idx,int delta)
{
  for(idx+=n;idx;idx>>=1) tree[idx]+=delta;
}

void build()
{
  for(int i=n-2;i;i--) tree[i]=tree[i<<1]+tree[(i<<1)|1]; 
}

int main()
{
  int nn;
  cin>>nn;
  nn+=2; //底层的第1和n个节点空闲 ，转开区间用 
  for(n=1;n<nn;n<<=1);
  for(int i=1;i<=nn-2;i++) { 
    cin>>tree[i+n];
  }
  build();
  int m;
  cin>>m;
  while(m--) {
    int c,l,r,v;
    cin>>c;
    if(c==1) {
      cin>>l>>r; //l,r属于[1,nn]
      cout<<qur(l,r)<<endl;
    } else {
      cin>>l>>v;
      alter(l,v);
    }
  }
  return 0;
}
