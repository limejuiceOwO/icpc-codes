#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> enemies[1000];
int ufs[1000];

int root(int a)
{
  if(ufs[a]!=a) return ufs[a]=root(ufs[a]);
  return a;
}

void uni(int a,int b)
{
  ufs[root(a)]=root(b);
}

int main()
{
  int n,m;
  cin>>n>>m;
  for(int i=0;i<n;i++)
    ufs[i]=i;
  while(m--) {
    char cmd;
    int a,b;
    cin>>cmd>>a>>b;
    a--;b--;
    if(cmd=='F') uni(a,b);
    else {
      enemies[b].push_back(a);
      enemies[a].push_back(b);
      for(vector<int>::iterator i=enemies[b].begin();i!=enemies[b].end();i++)
        uni(a,*i);
      for(vector<int>::iterator i=enemies[a].begin();i!=enemies[a].end();i++)
        uni(b,*i);
    }
  }
  int cnt=0;
  for(int i=0;i<n;i++)
    if(root(i)==i) cnt++;
  cout<<cnt<<endl;
  return 0;
}
