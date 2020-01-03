#include<iostream>
#include<algorithm>
using namespace std;
int dp[40][40][40][40];
int card[4];
int b[1000];

int main()
{
  int n,m;
  cin>>n>>m;
  for(int i=0;i<n;i++)
    cin>>b[i];
  for(int i=0;i<m;i++) {
    int k;
    cin>>k;
    card[k-1]++;
  }
  dp[0][0][0][0]=b[0];
  for(int i=0;i<=card[0];i++)
    for(int j=0;j<=card[1];j++)
      for(int k=0;k<=card[2];k++)
        for(int l=0;l<=card[3];l++) {
          if(i>0) dp[i][j][k][l]=max(dp[i][j][k][l],dp[i-1][j][k][l]+b[i+2*j+3*k+4*l]);
          if(j>0) dp[i][j][k][l]=max(dp[i][j][k][l],dp[i][j-1][k][l]+b[i+2*j+3*k+4*l]);
          if(k>0) dp[i][j][k][l]=max(dp[i][j][k][l],dp[i][j][k-1][l]+b[i+2*j+3*k+4*l]);
          if(l>0) dp[i][j][k][l]=max(dp[i][j][k][l],dp[i][j][k][l-1]+b[i+2*j+3*k+4*l]);
        }
  cout<<dp[card[0]][card[1]][card[2]][card[3]];
  return 0;
}

