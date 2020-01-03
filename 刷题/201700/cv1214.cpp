#include<iostream>
#include<algorithm>
using namespace std;

struct line {
  int s,e;
  bool operator <(line rsh) const{
      return e<rsh.e;
  }
} lines[1000];

int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    int s,e;
    cin>>s>>e;
    lines[i].s=min(s,e);
    lines[i].e=max(s,e);
  }
  sort(lines,lines+n);
  int e=-1000,cnt=0;
  for(int i=0;i<n;i++)
    if(e<=lines[i].s) {
      e=lines[i].e;
      cnt++;
    }
  cout<<cnt;
  return 0;
}
