#include<iostream>
#include<cstring>
using namespace std;
char maze[20][20];
char vis[20][20];
int n;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

bool dfs(int x,int y)
{
  if(x == n-1 && y == n-1) return true;
  vis[x][y] = 1;
  for(int i=0;i<4;i++) {
    int x2 = x + dx[i],y2 = y + dy[i];
    if(x2 >= 0 && y2 >= 0 && x2 < n \
    && y2 < n && maze[x2][y2] != '#'&&!vis[x2][y2])
      if(dfs(x2,y2)) return true;
  }
  return false;
}

int main()
{
  int m;
  cin >> m;
  while(m--) {
    cin >> n;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)
      cin >> maze[i];
    if(dfs(0,0)) cout << "YES\n";
    else cout << "NO\n";
  }
  return 0; 
}
