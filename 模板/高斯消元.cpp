#include<bits/stdc++.h>
#define N 20
using namespace std;

double A[N][N],B[N],ans[N];

bool gauss(int n)
{
  int repr[N];
  fill(repr,repr+n,-1);
  for(int i=0;i<n;i++) {
    for(int k=0;k<n;k++)
      if(A[i][k]) {
        repr[i]=k;
        break;
      }
    if(repr[i]<0) return false;
    double rr=A[i][repr[i]];
    for(int k=0;k<n;k++)
      A[i][k]/=rr;
    B[i]/=rr;
    for(int j=0;j<n;j++) {
      if(j!=i) {
        double r=A[j][repr[i]];
        for(int k=0;k<n;k++) {
          A[j][k]-=A[i][k]*r;
        }
        B[j]-=B[i]*r;
      }
    }
  }
  for(int i=0;i<n;i++)
    ans[repr[i]]=B[i];
  return true;
}

int main()
{
  freopen("gauss.in","r",stdin);
  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++)
      cin>>A[i][j];
    cin>>B[i];
  }
  gauss(n);
  for(int i=0;i<n;i++)
    cout<<(char)('a'+i)<<" = "<<ans[i]<<endl;
  return 0;
}
