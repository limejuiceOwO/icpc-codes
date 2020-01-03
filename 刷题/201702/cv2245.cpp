#include <iostream>
#include <algorithm>
#include <cstring>
#define N 805
using namespace std;

int arr[N],constraint[30];
int dp[N][N],maxarr[N][N][13];

int main()
{
  cin.sync_with_stdio(false);
  string s1,s2;
  cin>>s1>>s2;
  int l1=s1.length(),l2=s2.length();
  int k;
  cin>>k;
  while(k--) {
    fill(constraint,constraint+27,1000);
    while(1) {
      string c;
      int x;
      cin>>c;
      if(c[0]=='$') break;
      cin>>x;
      constraint[c[0]-'A']=x+1;
    }
    int ans=0;
    for(int i=1;i<=l1;i++) {
      for(int j=1;j<=l2;j++) {
        if(s1[i-1]==s2[j-1]) {
          int &cd=dp[i][j];
          int z=1,cr=constraint[s1[i-1]-'A'];
          while((1<<z)<=cr) z++;
          z--;
          const int i2=i-cr+(1<<z)-1,j2=j-cr+(1<<z)-1;
          cd=maxarr[i-1][j-1][z];
          if(i2>=0) cd=max(cd,maxarr[i2][j-1][z]);
          if(j2>=0) cd=max(cd,maxarr[i-1][j2][z]);
          if(i2>=0&&j2>=0) cd=max(cd,maxarr[i2][j2][z]);
          maxarr[i][j][0]=++cd;
          ans=max(ans,cd);
        }
        for(int k=1;k<=11;k++) {
          const int i2=i-(1<<(k-1)),j2=j-(1<<(k-1));
          int &mx=maxarr[i][j][k];
          mx=maxarr[i][j][k-1];
          if(i2>=0) mx=max(mx,maxarr[i2][j][k-1]);
          if(j2>=0) mx=max(mx,maxarr[i][j2][k-1]);
          if(i2>=0&&j2>=0) mx=max(mx,maxarr[i2][j2][k-1]);
        }
      }
    }
    cout<<ans<<" ";
  }
  return 0;
}
