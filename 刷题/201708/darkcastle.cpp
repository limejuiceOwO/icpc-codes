#include <iostream>
#include <algorithm>
#define INF 100000005
#define N 1005
using namespace std;

struct Point {
	int id,d;
	bool operator <(const Point &rhs) const {
		return d<rhs.d;
	}
	Point() {
		d=INF;
	}
} poi[N];
int w[N][N];
char vis[N];
int n;

void djst(int st)
{
	poi[st].d=0;
	for(int c=0;c<n;c++) {
		int mnd=INF,u=0;
		for(int i=1;i<=n;i++) {
			if(!vis[i]&&poi[i].d<mnd) {
				mnd=poi[i].d;
				u=i;
			}
		}
		vis[u]=1;

		for(int i=1;i<=n;i++) {
			if(w[u][i]) {
				poi[i].d=min(poi[i].d,poi[u].d+w[u][i]);
			}
		}
	}
}

int main()
{
	int m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int u,v,ww;
		cin>>u>>v>>ww;
		w[u][v]=w[v][u]=ww;
	}

	for(int i=1;i<=n;i++) {
		poi[i].id=i;
	}
	djst(1);
	sort(poi+1,poi+n+1);

	unsigned int ans=1;
	for(int i=2;i<=n;i++) {
		unsigned int cnt=0;
		for(int j=1;j<i;j++) {
			if(poi[j].d+w[poi[j].id][poi[i].id]==poi[i].d) {
				cnt++;
			}
		}
		ans*=cnt;
	}

	cout<<ans<<endl;
	return 0;
}