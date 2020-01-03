#include<iostream>
#include<algorithm>
using namespace std;

struct line {
  int s,e;
  bool operator <(line rsh) const{
      return s>rsh.s;
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
  int s=1000,cnt=0;
  for(int i=0;i<n;i++)
    if(s>=lines[i].e) {
      s=lines[i].s;
      cnt++;
    }
  cout<<cnt;
  return 0;
}
