#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("spfa.txt","w",stdout);
  const int n=1000;
  srand(time(0)+2333);
  printf("%d %d %d %d\n",n,n*(n+1)/2,1,n);
  for(int i=1;i<=n;i++) {
    for(int j=i;j<=n;j++) {
      printf("%d %d %d\n",i,j,rand());
    }
  }
  return 0;
}
