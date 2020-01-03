//联想显示屏校准 莫比乌斯反演（变态级）
#include <iostream>
#include <algorithm>
#define N 400005
using namespace std;

long long prime[N],mindiv[N];
long long mu[N],dmu[N],d2mu[N];
int pcnt;

void sieve()
{
	mindiv[1]=mu[1]=1;
	for(int i=2;i<N;i++) {
		if(!mindiv[i]) {
			prime[pcnt++]=mindiv[i]=i;
			mu[i]=-1;
		}
		for(int j=0;j<pcnt&&prime[j]*i<N;j++) {
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

unsigned int calc1(unsigned int n,unsigned int m)
{
	unsigned int ans=0;
	for(unsigned int i=1,d;i<=min(n-1,m-1);i=d+1) {
		d=min((n-1)/((n-1)/i),(m-1)/((m-1)/i));
		unsigned int p=(n-1)/i,q=(m-1)/i;
		unsigned int pp=(long long)p*(p+1)/2,qq=(long long)q*(q+1)/2;
		ans+=p*q*n*m*(mu[d]-mu[i-1])
			+(d2mu[d]-d2mu[i-1])*(pp*qq)
			-(dmu[d]-dmu[i-1])*(pp*m*q+qq*n*p);  //这货什么鬼……
	}
	return ans;
}

unsigned int calc2(unsigned int n,unsigned int m)
{
	unsigned int nn=n/2,mm=m/2;
	unsigned int ans=0;
	for(unsigned int i=1,d;i<=min(nn,mm);i=d+1) {
		d=min(nn/(nn/i),mm/(mm/i));
		unsigned int p=nn/i,q=mm/i;
		ans+=p*q*n*m*(mu[d]-mu[i-1])
			+(p*q*(p+1)*(q+1))*(d2mu[d]-d2mu[i-1])
			-(m*p*(p+1)*q+n*q*(q+1)*p)*(dmu[d]-dmu[i-1]); //@_@
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	int t;
	cin>>t;

	sieve();
	for(long long i=1;i<N;i++) {
		dmu[i]=dmu[i-1]+i*mu[i];
		d2mu[i]=d2mu[i-1]+i*i*mu[i];
		mu[i]+=mu[i-1];
	}

	while(t--) {
		int n,m;
		cin>>n>>m;
		unsigned int ans=((calc1(n,m)-calc2(n,m))*2+n+m)&~(~0U<<30);
		cout<<ans<<endl;
	}

	return 0;
}