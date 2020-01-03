//导弹拦截
#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

pair<int,int> dist[N];

inline int D(int x,int y) { return x*x+y*y; }

int main()
{
	ios::sync_with_stdio(false);
	int x1,y1,x2,y2,n;
	cin>>x1>>y1>>x2>>y2>>n;
	for(int i=0;i<n;i++) {
		int x,y;
		cin>>x>>y;
		dist[i]=make_pair(D(x-x1,y-y1),D(x-x2,y-y2));
	}
	sort(dist,dist+n);
	int ans=10000000,p=0;
	for(int i=n-1;i>=0;i--) {
		ans=min(ans,dist[i].first+p);
		p=max(p,dist[i].second);
	}
	cout<<ans<<endl;
	return 0;
}