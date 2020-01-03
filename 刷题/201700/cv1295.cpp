#include <iostream>
#include <algorithm>
#define N 15
using namespace std;

int pos[N];
int n;
long long cnt;

bool usable(int d,int p)
{
  for(int i=0;i<d;i++) {
    if(pos[i]==p||pos[i]-(d-i)==p||pos[i]+(d-i)==p) {
      return false;
    }
  }
  return true;
}

void solve(int d)
{
  if(d==n) {
    ++cnt;
    return;
  }
  for(int i=0;i<n;i++) {
    if(usable(d,i)) {
      pos[d]=i;
      solve(d+1);
    }
  }
}

int main()
{
  cin>>n;
  solve(0);
  cout<<cnt<<endl;
  return 0;
}
