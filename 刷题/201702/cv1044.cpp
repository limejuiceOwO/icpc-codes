//拦截导弹
#include <iostream>
#include <algorithm>
#define N 30005
using namespace std;

int dis[N],dis2[N];

int main()
{
	int n;
	cin>>n;
	int ans1=0,ans2=0;
	for(int i=0;i<n;i++) {
		int val;
		cin>>val;
		int p1=lower_bound(dis,dis+i,val)-dis,p2=lower_bound(dis2,dis2+i,val,greater<int>)-dis2;
		dis[p1]=dis2[p2]=val;
		ans1=max(ans1,p1);
		ans2=max(ans2,p2);
	}
	cout<<ans1<<" "<<ans2<<endl;
	return 0;
}