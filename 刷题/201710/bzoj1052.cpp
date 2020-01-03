#include <iostream>
#include <algorithm>
#include <cstring>
#define N 20005
#define INF 100000005
using namespace std;

struct Point {
	int x,y;
	bool operator <(const Point &rhs) const {
		return x<rhs.x;
	}
} point[N];

char cov[N];
int n;

bool mark(int l,int ub1,int ub2)
{
	for(int i=0;i<n;i++) {
		if(point[i].x-point[0].x<=l&&point[i].y>=ub1&&point[i].y<=ub1+l)
			cov[i]=1;
		if(point[n-1].x-point[i].x<=l&&point[i].y>=ub2&&point[i].y<=ub2+l)
			cov[i]=1;
	}

	int u=-INF,d=INF,ll=INF,r=-INF;
	for(int i=0;i<n;i++) {
		if(cov[i]) continue;
		u=max(u,point[i].y);
		d=min(d,point[i].y);
		ll=min(ll,point[i].x);
		r=max(r,point[i].x);
	}
	return u-d<=l&&r-ll<=l;
}

bool check(int l)
{
	int u1=point[0].y,d1=point[0].y,u2=point[n-1].y,d2=point[n-1].y;
	for(int i=0;i<n;i++) {
		if(point[i].x-point[0].x<=l) {
			u1=max(u1,point[i].y);
			d1=min(d1,point[i].y);
		}
		if(point[n-1].x-point[i].x<=l) {
			u2=max(u2,point[i].y);
			d2=min(d2,point[i].y);
		}
	}

	memset(cov,0,sizeof(cov));
	if(mark(l,u1,u2)) return true;
	memset(cov,0,sizeof(cov));
	if(mark(l,u1,d2+l)) return true;
	memset(cov,0,sizeof(cov));
	if(mark(l,d1+l,u2)) return true;
	memset(cov,0,sizeof(cov));
	if(mark(l,d1+l,d2+l)) return true;

	return false;
}

int main()
{
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>point[i].x>>point[i].y;
	}
	sort(point,point+n);

	int lb=1,rb=point[n-1].x-point[0].x;
	while(lb<rb) {
		int mid=(lb+rb)>>1;
		if(check(mid)) lb=mid+1;
		else rb=mid;
	}

	cout<<lb-1<<endl;
	return 0;
}