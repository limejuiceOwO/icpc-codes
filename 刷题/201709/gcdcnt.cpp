//求gcd(i,j)=k的(i,j)对数 莫比乌斯反演
#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

int mu[N];
int mindiv[N],prime[N];
int pcnt;

void sieve(int n)
{
	mindiv[1]=mu[1]=1;
	for(int i=2;i<n;i++) {
		if(!mindiv[i]) {
			prime[pcnt++]=mindiv[i]=i;
			mu[i]=-1;
		}
		for(int j=0;j<pcnt&&prime[j]*i<n;j++) {
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

int main()
{
	ios::sync_with_stdio(false);

	int t;
	cin>>t;

	sieve(N);
	for(int i=2;i<N;i++) {
		mu[i]+=mu[i-1];
	}
	while(t--) {
		int n,m,k;
		cin>>n>>m>>k;

		n/=k;
		m/=k;
		long long ans=0,d;
		for(long long i=1;i<=min(n,m);i=d+1) {
			d=min(n/(n/i),m/(m/i));
			//cout<<d<<endl;
			ans+=(long long)(mu[d]-mu[i-1])*(n/d)*(m/d);
		}
		cout<<ans<<endl;
	}

	return 0;
}