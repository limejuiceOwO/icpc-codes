#include <iostream>
#include <algorithm>
#include <cmath>
#define N 5005
using namespace std;

int cnt[N],dv[N];
int dcnt;

int gcd(int a,int b)
{
	while(b) {
		int t=b;
		b=a%b;
		a=t;
	}
	return a;
}

int lcm(int a,int b)
{
	return a*b/gcd(a,b);
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;

	int ub=sqrt(m)+1;
	for(int i=1;i<ub;i++) {
		if(m%i==0) {
			dv[dcnt++]=i;
			dv[dcnt++]=m/i;
		}
	}

	sort(dv,dv+dcnt);

	for(int i=0;i<n;i++) {
		int x;
		cin>>x;

		int g=gcd(m,x);
		int pos=lower_bound(dv,dv+dcnt,g)-dv;
		for(int j=dcnt-1;j>=0;j--) {
			int d=dv[j];
			int pos2=lower_bound(dv,dv+dcnt,lcm(g,d))-dv;
			cnt[pos2]-=cnt[j];
		}
		cnt[pos]++;
	}
	
	long long ans=0;
	for(int i=0;i<dcnt;i++) {
		ans+=(long long)cnt[i]*(m/dv[i]-1)*m/2;
	}

	cout<<ans<<endl;
	return 0;
}