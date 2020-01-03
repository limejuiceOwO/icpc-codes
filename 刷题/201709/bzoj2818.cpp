//GCD 莫比乌斯反演
#include <iostream>
#include <algorithm>
#define N 10000005
using namespace std;

int mu[N];
int mindiv[N],prime[N];
int n,pcnt;

void sieve(int n)
{
	mindiv[1]=mu[1]=1;
	for(int i=2;i<=n;i++) {
		if(!mindiv[i]) {
			prime[pcnt++]=mindiv[i]=i;
			mu[i]=-1;
		}
		for(int j=0;j<pcnt&&prime[j]*i<=n;j++) {
			mindiv[prime[j]*i]=prime[j];
			if(mindiv[i]==prime[j]) {
				mu[prime[j]*i]=0;
				break;
			} else {
				mu[prime[j]*i]=-mu[i];
			}
		}
	}
}

long long calc(long long p)
{
	long long ans=0;
	long long nn=n/p;
	for(long long i=1,d;i<=nn;i=d+1) {
		d=nn/(nn/i);
		ans+=(long long)(mu[d]-mu[i-1])*(nn/d)*(nn/d);
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	cin>>n;
	sieve(n);
	for(int i=2;i<=n;i++) {
		mu[i]+=mu[i-1];
	}
	
	long long ans=0;
	for(int i=0;i<pcnt;i++) {
		ans+=calc(prime[i]);
	}

	cout<<ans<<endl;

	return 0;
}