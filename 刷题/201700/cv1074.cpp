//食物链 边权解法
#include<iostream>
#include<algorithm>
using namespace std;

int ufs[50000];
int rel[50000];

int root(int u)
{
  if(u==ufs[u]) return u;
  int r=root(ufs[u]);
  rel[u]=(rel[u]+rel[ufs[u]])%3;
  return ufs[u]=r;
}

void uni(int a,int b,int m)
{
  int r=root(a);
  rel[r]=(m-rel[a]+3)%3;//错误：rel[r]=m
  ufs[r]=b;
}

int main()
{
  int n,k;
  cin>>n>>k;
  for(int i=0;i<n;i++)
    ufs[i]=i;
  int fake=0;
  while(k--) {
    int cmd,a,b;
    cin>>cmd>>a>>b;
    a--;b--;cmd--;
    if(a>=n||b>=n) {
      fake++;
      continue;
    }
    if(root(a)==root(b)) {
      if((rel[a]-rel[b]+3)%3!=cmd) {
        cout<<"fake"<<endl;
        fake++;
      }
    } else {
      uni(a,b,cmd);
    }
  }
  cout<<fake<<endl;
  return 0;
}
