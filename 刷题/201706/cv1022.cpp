#include <iostream>
#include <algorithm>
#include <cstring>
#define N 105
using namespace std;

int n,m;
int matchx[N][N],matchy[N][N];
char vis[N][N],illegal[N][N];

const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

bool legal(int x,int y)
{
	return x>0&&y>0&&x<=n&&y<=m&&!illegal[x][y];
}

int dfs(int x,int y)
{
	vis[x][y]=1;
	if(illegal[x][y]) return 0;

	for(int i=0;i<4;i++) {
		int nx=x+dx[i],ny=y+dy[i];
		if(legal(nx,ny)&&(!matchx[nx][ny]||(!vis[matchx[nx][ny]][matchy[nx][ny]]&&dfs(matchx[nx][ny],matchy[nx][ny])))) {
			matchx[nx][ny]=x;
			matchy[nx][ny]=y;
			return 1;
		}
	}

	return 0;
}

int bimatch()
{
	int ans=0;
	for(int x=1;x<=n;x++) {
		for(int y=(x&1)+1;y<=m;y+=2) {
			memset(vis,0,sizeof(vis));
			ans+=dfs(x,y);
		}
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	int k;
	cin>>n>>m>>k;
	for(int i=0;i<k;i++) {
		int x,y;
		cin>>x>>y;
		illegal[x][y]=1;
	}

	cout<<bimatch()<<endl;
	return 0;
}