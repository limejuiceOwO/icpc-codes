//zkw线段树 二维版...
#include <iostream>
#include <algorithm>
#define K 9
const int N=2*(1<<K)+10; 
using namespace std;

int tree[N][N];
int n,m;

void build()
{
  for(int p=n;p<=2*n;p++) {
    for(int p2=m-1;p2;p2--) {
        tree[p][p2]=tree[p][p2<<1]+tree[p][p2<<1|1];
    }
  }
  for(int p=n-1;p;p--) {
    for(int p2=m;p2<=2*m;p2++) {
        tree[p][p2]=tree[p<<1][p2]+tree[p<<1|1][p2];
    }
    for(int p2=m-1;p2;p2--) {
        tree[p][p2]=tree[p][p2<<1]+tree[p][p2<<1|1];
    }
  }
}

int qur(int x1,int y1,int x2,int y2)
{
  int ans=0;
  for(x1+=n-1,x2+=n+1;(x1^x2)^1;x1>>=1,x2>>=1) {
    for(int yy1=y1+m-1,yy2=y2+m+1;(yy1^yy2)^1;yy1>>=1,yy2>>=1) {
      if(!(x1&1)) {
        if(!(yy1&1)) ans+=tree[x1^1][yy1^1];
        if(yy2&1) ans+=tree[x1^1][yy2^1];
      }
      if(x2&1) {
        if(!(yy1&1)) ans+=tree[x2^1][yy1^1];
        if(yy2&1) ans+=tree[x2^1][yy2^1];
      }
    }
  }
  return ans;
}

void alter(int x,int y,int delta)
{
  for(x+=n;x;x>>=1) {
    for(int yy=y+n;yy;yy>>=1) {
      tree[x][yy]+=delta;
    }
  }
}

int main()
{
  int nn,mm;
  cin>>nn>>mm;
  nn+=2,mm+=2;
  for(n=1;n<nn;n<<=1);
  for(m=1;m<mm;m<<=1);
  for(int i=1;i<=nn-2;i++) {
    for(int j=1;j<=mm-2;j++) {
        cin>>tree[i+n][j+m];
    }
  }
  build();
  while(1) {
    int c,x1,x2,y1,y2,val;
    cin>>c;
    if(c==1) {
      cin>>x1>>x2>>y1>>y2;
      cout<<qur(x1,x2,y1,y2)<<endl;
    } else {
      cin>>x1>>y1>>val;
      alter(x1,y1,val);
    }
  }
  return 0;
}
