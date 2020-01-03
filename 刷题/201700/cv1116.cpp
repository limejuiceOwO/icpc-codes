#include<iostream>
using namespace std;
int v[8];
int G[8][8];
int n;

int dfs(int u,int r)
{
  int ans=r;
  if(r<=1) return 1;
  v[u]=1;
  for(int i=0;i<n;i++)
    if(G[u][i]&&!v[i]) ans*=dfs(i,r-1);
  return ans;
}

int main()
{
  int ans=1;
  cin>>n;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++) {
      int be;
      cin>>be;
      if(be) G[i][j]=1;
    }
  for(int i=0;i<n;i++)
    ans*=dfs(i,4);
  cout<<ans;
  return 0;
}
