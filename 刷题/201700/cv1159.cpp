#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int k[5],nk[5],dpos[5][2],vd[5];
char maze[30][30];
bool v[20][20];
int m,n;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

bool dfs(int x,int y)
{
  char c=maze[x][y];
  v[x][y]=1;
  if(c=='G') return true;
  if(c=='X') return false;
  if(c-'A'>=0&&c-'E'<=0) {
    vd[c-'A']=1;
    return false;
  }
  if(c-'a'>=0&&c-'e'<=0) {
    k[c-'a']++;
    maze[x][y]='.';
  }
  for(int i=0;i<4;i++) {
    int x2=x+dx[i],y2=y+dy[i];
    if(x2>=0&&x2<m&&y2>=0&&y2<n&&!v[x2][y2]&&dfs(x2,y2)) return true;
  }
  return false;
}

int main()
{
  int sx,sy;
  while(1) {
begin:
    memset(v,0,sizeof(v));
    memset(k,0,sizeof(k));
    memset(nk,0,sizeof(nk));
    memset(vd,0,sizeof(vd));
    //scanf("%d%d",&m,&n);
    //getchar();
    cin >> m >> n;
    if(m==0&&n==0) return 0;
    for(int i=0;i<m;i++) {
      //fgets(maze[i],30,stdin);
      cin >> maze[i];
      for(int j=0;j<n;j++) {
        char c=maze[i][j];
        if(c=='S') {
          sx=i;sy=j;
        } else if(c-'A'>=0&&c-'E'<=0) {
          dpos[c-'A'][0]=i;
          dpos[c-'A'][1]=j;
        } else if(c-'a'>=0&&c-'e'<=0)
          nk[c-'a']++;
      }
    }
    while(!dfs(sx,sy)) {
      int door=0;
      for(int i=0;i<5;i++) {
        //printf("%d %d %d\n",k[i],nk[i],vd[i]);
        if(vd[i]&&k[i]>=nk[i]) {
            door=1;
            vd[i]=0;
            maze[dpos[i][0]][dpos[i][1]]='.';
        }
      }
      if(!door) {
          puts("NO");
          goto begin;
      }
      memset(v,0,sizeof(v));
    }
    puts("YES");
  }
  return 0;
}
//R.M.T!R.M.T!
