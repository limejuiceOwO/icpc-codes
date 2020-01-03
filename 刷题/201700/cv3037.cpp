#include<iostream>
#include<algorithm>
using namespace std;

struct line {
  int s,e,v;
  bool operator <(line rsh) const{
      return e<rsh.e;
  }
} lines[1000000];

int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    int s,e,v;
    cin>>s>>e>>v;
    lines[i].s=s;
    lines[i].e=e;
    lines[i].v=v;
  }
  sort(lines,lines+n);
  for(int i=0;i<n;i++)
    if(e<=lines[i].s) {
      e=lines[i].e;
      cnt++;
    }
  cout<<cnt;
  return 0;
}
