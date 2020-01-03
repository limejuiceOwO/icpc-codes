
#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<list>
#include<cstring>
using namespace std;

int p[1000];

void union(int a,int b) //a and b are root nodes
{
  p[a]=b;
}
void find(int a)
{
  return p[a]==a?a:p[a]=find[a];
}
void same(int a,int b)
{
  return find(a)==find(b);
}

int main()
{
  for(int i=0;i<1000;i++)
    p[i]=i;
  return 0;
}
