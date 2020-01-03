#include <iostream>
#include <algorithm>
#include <cstring>
#define N 5005
using namespace std;

const double EPS=1e-8;
double px1[N],px2[N];
int ans[N];

inline double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}

int main()
{
	int n,m;
	ios::sync_with_stdio(false);
	double cx1,cx2,cy1,cy2;
	while(1) {
		cin>>n;
		if(n==0) break;
		cin>>m>>cx1>>cy1>>cx2>>cy2;
		for(int i=0;i<n;i++) cin>>px1[i]>>px2[i];
		memset(ans,0,sizeof(ans));
		for(int i=0;i<m;i++) {
			double tx,ty;
			cin>>tx>>ty;
			int p=0;
			while(p<n&&det(tx-px1[p],ty-cy1,px2[p]-px1[p],cy2-cy1)<=EPS) p++;
			ans[p]++;
		}
		for(int i=0;i<=n;i++) cout<<i<<": "<<ans[i]<<endl;
		cout<<endl;
	}
	return 0;
}