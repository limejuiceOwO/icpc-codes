//NOIP2015 信息传递
#include <iostream>
#include <algorithm>
using namespace std;

int to[1000000];
int d[1000000];

int main()
{
  cin.sync_with_stdio(false);
  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    cin>>to[i];
    to[i]--;
  }
  int minr=1000000,id=1;
  for(int i=0;i<n;i++) {
    int cur=i,lastid=id;
    while(d[cur]==0) {
      d[cur]=id++;
      cur=to[cur];
    }
    if(d[cur]>=lastid) minr=min(minr,id-d[cur]);
  }
  cout<<minr<<endl;
  return 0;
}
