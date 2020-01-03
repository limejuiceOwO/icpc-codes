#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 505
using namespace std;

char map[N][N],vis[N][N][3];
const int dx[]={0,1,0},dy[]={0,0,1}; //0立1竖2横
const int ddy[][4]={{0,0,-2,1},{0,0,-1,1},{0,0,-1,2}},ddx[][4]={{-2,1,0,0},{-1,2,0,0},{-1,1,0,0}},ddc[][4]={{1,1,2,2},{0,0,1,1},{2,2,0,0}};
struct Stat {
	int x,y,c,d;
};

Stat mov(const Stat &cur,int d) //0上1下2左3→
{
	return (Stat) {cur.x+ddx[cur.c][d],cur.y+ddy[cur.c][d],ddc[cur.c][d],cur.d+1};
}

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		int n,m;
		cin>>n>>m;
		if(n+m==0) break;

		for(int i=0;i<n;i++)
			cin>>map[i];

		int stx=0,sty=0,stc=0;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				if(map[i][j]=='X') {
					stx=i,sty=j;
					if(map[i+1][j]=='X')
						stc=1;
					else if(map[i][j+1]=='X')
						stc=2;
					goto out;
				}
			}
		}

		out:
		int ans=-1;
		queue<Stat> q;
		q.push((Stat) {stx,sty,stc,0});
		vis[stx][sty][stc]=1;
		memset(vis,0,sizeof(vis));
		while(!q.empty()) {
			Stat cur=q.front();q.pop();
			if(cur.c==0&&map[cur.x][cur.y]=='O') {
				ans=cur.d;
				break;
			}
			for(int i=0;i<4;i++) {
				Stat nxt=mov(cur,i);
				if(map[nxt.x][nxt.y]=='#'||map[nxt.x+dx[nxt.c]][nxt.y+dy[nxt.c]]=='#')
					continue;
				if(nxt.c==0&&map[nxt.x][nxt.y]=='E')
					continue;
				if(vis[nxt.x][nxt.y][nxt.c])
					continue;
				vis[nxt.x][nxt.y][nxt.c]=1;
				q.push(nxt);
			}
		}

		if(ans<=0)
			cout<<"Impossible"<<endl;
		else
			cout<<ans<<endl;
	}
	return 0;
}