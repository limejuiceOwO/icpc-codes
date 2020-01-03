#include <iostream>
#include <algorithm>
#define N 40005
using namespace std;

int phi[N],mindiv[N],prime[N];

void sieve(int n)
{
	int cnt=0;
	phi[1]=1;
	for(int i=2;i<=n;i++) {
		if(!mindiv[i]) {
			prime[cnt++]=i;
			mindiv[i]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<cnt&&prime[j]<=mindiv[i]&&i*prime[j]<=n;j++) {
			mindiv[prime[j]*i]=prime[j];
			phi[prime[j]*i]=(prime[j]==mindiv[i])?phi[i]*prime[j]:phi[i]*(prime[j]-1);
		}
	}
}

int main()
{
	int n;
	cin>>n;

	if(n==1) {
		cout<<"0"<<endl;
		return 0;
	}

	sieve(n);

	long long ans=0;
	for(int i=1;i<=n-1;i++)
		ans+=phi[i];

	cout<<ans*2+1<<endl;
	return 0;
}