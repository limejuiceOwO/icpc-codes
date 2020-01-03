#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 35
#define INF 10000005
using namespace std;

struct Stat {
	int x,y,d;
};

const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1},rev[4]={1,0,3,2};
const int rot[2][4]={{-1,1,-1,1},{1,-1,1,-1}},rotd[2][4]={{3,2,0,1},{2,3,1,0}};
int board[N][N];
int cost[N][N],cost2[N][N][4];
int n,m;

bool valid(int x,int y)
{
	return x>=0&&y>=0&&x<n&&y<m&&board[x][y];
}

int bfs1(int sx,int sy,int tx,int ty)
{
	if(sx==tx&&sy==ty) return 0;
	if(!valid(sx,sy)) return INF;

	queue<pair<int,int>> que;
	que.push(make_pair(sx,sy));
	memset(cost,0,sizeof(cost));
	cost[sx][sy]=1;

	while(!que.empty()) {
		int x=que.front().first,y=que.front().second;
		que.pop();

		for(int i=0;i<4;i++) {
			int nx=x+dx[i],ny=y+dy[i];
			if(!valid(nx,ny)||cost[nx][ny]) continue;
			cost[nx][ny]=cost[x][y]+1;
			if(nx==tx&&ny==ty) return cost[nx][ny]-1;
			que.push(make_pair(nx,ny));
		}
	}

	return INF;
}

int bfs2(int sx,int sy,int d,int tx,int ty)
{
	if(sx==tx&&sy==ty) return 0;
	if(!valid2(sx,sy)) return INF;

	queue<Stat> que;
	que.push((Stat) {sx,sy,d});
	memset(cost,0,sizeof(cost));
	cost[sx][sy]=1;

	while(!que.empty()) {
		Stat st=que.front();
		int x=st.x,y=st.y,d=st.d;
		que.pop();

		int nx=x+dx[d],ny=y+dy[d];
		if(valid(nx,ny)&&!cost2[nx][ny][rev[d]]) {
			cost2[nx][ny][rev[d]]=cost2[x][y][d]+1;
			que.push((Stat) {nx,ny,rev[d]});
		}

		for(int i=0;i<2;i++) {
			int nx=st.x+rot[i][d],ny=st.y+rot[i][d];
			if(valid(nx,ny)&&!cost2[x][y][rotd[i][d]]) {
				cost2[x][y][rotd[i][d]]=cost2[x][y][d]+2;
				que.push((Stat) {x,y,rotd[i][d]});
			}
		}
	}

	int ans=INF;
	for(int i=0;i<4;i++)
		ans=min(ans,cost2[tx][ty][i]);
	return ans==INF ? INF : ans-1;
}

int main()
{
	int q;
	cin>>n>>m>>q;

	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>board[i][j];
		}
	}

	while(q--) {
		int ans=INF;
		int sx,sy,ex,ey,tx,ty;
		cin>>ex>>ey>>sx>>sy>>tx>>ty;
		sx--,sy--,ex--,ey--,tx--,ty--;
		for(int i=0;i<4;i++) {
			int a,b;
			board[sx][sy]=0;
			a=bfs1(ex,ey,sx+dx[i],sy+dy[i]);
			board[sx][sy]=1;
			ans=min(ans,a+(b=bfs2(sx,sy,i,tx,ty)));
			cout<<i<<" "<<a<<" "<<b<<endl;
		}

		if(ans==INF)
			cout<<"-1"<<endl;
		else
			cout<<ans<<endl;
	}


	return 0;
}