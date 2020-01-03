//3304 1263 2318
//TOYS
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
		//px1[n]=px2[n]=cx2;
		memset(ans,0,sizeof(ans));
		for(int i=0;i<m;i++) {
			double tx,ty;
			cin>>tx>>ty;
			int l=0,r=n;
			while(l<r) {
				int mid=l+((r-l)>>1);
				if(det(tx-px1[mid],ty-cy1,px2[mid]-px1[mid],cy2-cy1)>EPS) { //T在左边
					r=mid;
				} else {
					l=mid+1;
				}
			}
			ans[l]++;
		}
		for(int i=0;i<=n;i++) cout<<i<<": "<<ans[i]<<endl;
		cout<<endl;
	}
	return 0;
}