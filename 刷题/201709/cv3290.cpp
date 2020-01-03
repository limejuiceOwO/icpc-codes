//NOIP2013 华容道 预处理最短路+dijkstra
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define N 32
using namespace std;

int dis[N][N][4][N][N];
int d[N][N][4];
int board[N][N];

int n,m;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};//右0左1下2上3
const int dd[]={1,0,3,2};

struct Stat {
	int x,y,d,dis;
	bool operator <(const Stat &rhs) const {
		return dis>rhs.dis;
	}
};

bool vaild(int x,int y)
{
	return x>=0&&y>=0&&x<n&&y<m&&board[x][y];
}

void dij(int dis[N][N],int sx,int sy,int kx,int ky)
{
	memset(dis,0x7f,sizeof(int)*N*N);
	if(!vaild(sx,sy)) return;
	dis[sx][sy]=0;
	queue<pair<int,int> > que;
	que.push(make_pair(sx,sy));
	while(!que.empty()) {
		int x=que.front().first,y=que.front().second;
		que.pop();
		for(int d=0;d<4;d++) {
			int nx=x+dx[d],ny=y+dy[d];
			if(!vaild(nx,ny)||dis[nx][ny]<=10000005||(nx==kx&&ny==ky)) continue;
			dis[nx][ny]=dis[x][y]+1;
			que.push(make_pair(nx,ny));
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	int q;
	cin>>n>>m>>q;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>board[i][j];
		}
	}

	for(int x=0;x<n;x++) {
		for(int y=0;y<m;y++) {
			for(int d=0;d<4;d++) {
				int sx=x+dx[d],sy=y+dy[d];
				dij(dis[x][y][d],sx,sy,x,y);
			}
		}
	}

	while(q--) {
		int ex,ey,sx,sy,tx,ty;
		cin>>ex>>ey>>sx>>sy>>tx>>ty;
		ex--,ey--,sx--,sy--,tx--,ty--;

		if(sx==tx&&sy==ty) { //注意特判掉起点等于目标点的情况，此时不需要先移动空白格子
			cout<<"0"<<endl;
			continue;
		}

		memset(d,0x7f,sizeof(d));
		priority_queue<Stat> pq;
		for(int k=0;k<4;k++) {
			if(dis[sx][sy][k][ex][ey]>=10000005) //注意不要把INF加进队列，否则会爆int
				continue;
			d[sx][sy][k]=dis[sx][sy][k][ex][ey];
			pq.push((Stat) {sx,sy,k,dis[sx][sy][k][ex][ey]});
		}

		int ans=-1;
		while(!pq.empty()) {
			Stat cur=pq.top();pq.pop();
			int x=cur.x,y=cur.y;

			if(cur.dis>d[x][y][cur.d])
				continue;

			if(x==tx&&y==ty) {
				ans=cur.dis;
				break;
			}

			int nx=x+dx[cur.d],ny=y+dy[cur.d],nd=dd[cur.d];
			if(cur.dis+1<d[nx][ny][nd]) {
				Stat nxt=(Stat) {nx,ny,nd,cur.dis+1};
				d[nx][ny][nd]=cur.dis+1;
				pq.push(nxt);
			}

			for(int c=0;c<4;c++) { //三个方向都要转移
				if(c==cur.d) continue;
				int ndis=cur.dis+dis[x][y][cur.d][x+dx[c]][y+dy[c]];
				if(!vaild(x+dx[c],y+dy[c])||ndis>=d[x][y][c])
					continue;
				Stat nxt=(Stat) {x,y,c,ndis};
				d[x][y][c]=ndis;
				pq.push(nxt);
			}
		}

		cout<<ans<<endl;
	}

	return 0;
}