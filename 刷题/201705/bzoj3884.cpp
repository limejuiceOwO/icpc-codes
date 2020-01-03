#include <iostream>
#include <algorithm>
#include <cmath>
#define N 10000005
using namespace std;

int phi[N],prime[N];

long long qpow(long long x,long long k,long long p)
{
	long long ans=1;

	while(k) {

		if(k&1) ans=(ans*x)%p;

		x=(x*x)%p;
		k>>=1;
	}

	return ans;
}

void gen_phi()
{
	int cnt=0;

	phi[1]=1;

	for(long long i=2;i<N;i++) {

		if(!phi[i]) {
			prime[cnt++]=i;
			phi[i]=i-1;
		}

		for(int j=0;j<cnt&&(long long)prime[j]*i<N;j++) {

			if(!(i%prime[j])) {
				phi[prime[j]*i]=prime[j]*phi[i];
				break;
			} else {
				phi[prime[j]*i]=(prime[j]-1)*phi[i];
			}
		}
	}
}

long long calc(long long p)
{
	return p==1?0:qpow(2,calc(phi[p])+phi[p],p);
}

int main()
{
	int t;
	cin>>t;

	gen_phi();

	while(t--) {
		long long p;
		cin>>p;
		cout<<calc(p)<<endl;
	}

	return 0;
}