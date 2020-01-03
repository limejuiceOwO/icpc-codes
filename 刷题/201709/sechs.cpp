#include <iostream>
#include <algorithm>
#define N 45
using namespace std;

int bits[N];
int cnt;

long long f(long long n)
{
	long long ans=0;
	
	long long prefix=0;
	for(int i=cnt-1;i>=0;i--) {
		ans++;
		for(int j=(i==cnt-1 ? 1 : 0);j<bits[i];j++) {
			ans++;
			long long pw;
			for(pw=10;(prefix*10+j)*pw+pw-1<=n;pw*=10) {
				ans+=pw;
			}
			ans+=max(0LL,n-(prefix*10+j)*pw+1);
		}
		prefix=prefix*10+bits[i];
	}

	return ans;
}

int main()
{
	long long k,m;
	cin>>m>>k;

	long long l=m,r=(1LL<<57)-1;
	while(m) {
		bits[cnt++]=m%10;
		m/=10;
	}

	while(l<r) {
		long long mid=(l+r)>>1;
		//cout<<f(mid)<<endl;
		if(f(mid)<k)
			l=mid+1;
		else
			r=mid;
	}
	
	cout<<(l==(1LL<<57)-1 ? 0 : l)<<endl;

	return 0;
}