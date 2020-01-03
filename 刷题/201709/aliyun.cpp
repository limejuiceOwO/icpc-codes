#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define N 60
#define P 100005
using namespace std;

long long f[N][P],g[N][P];
long long mindiv[P],mu[P],prime[P];
long long p;
int pcnt;
vector<int> divisor[P];

void sieve()
{
	mindiv[1]=mu[1]=1;
	for(int i=2;i<P;i++) {
		if(!mindiv[i]) {
			prime[pcnt++]=mindiv[i]=i;
			mu[i]=-1;
		}
		for(int j=0;j<pcnt&&prime[j]*i<P;j++) {
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

long long gcd(long long a,long long b)
{
	while(b) {
		long long t=b;
		b=a%b;
		a=t;
	}

	return a;
}

long long calc(long long x)
{
	if(x==0) return 0;

	static int bits[N];
	int bcnt=0;
	while(x) {
		bits[bcnt++]=x%p;
		x/=p;
	}

	long long ans=0;
	int i;
	for(i=bcnt-1;i>0;i--) {
		for(int j=1;j<p;j++) {
			ans+=f[i][j];
		}
	}
	for(i=bcnt-1;i>=0;i--) {
		if(bits[i]==0) break;
		for(int j=1;j<bits[i];j++) {
			if(i<bcnt-1&&gcd(j,bits[i+1])!=1)
				continue;
			ans+=f[i+1][j];
		}
		if(i<bcnt-1&&gcd(bits[i],bits[i+1])!=1) break;
	}

	if(i<0) ans++;

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	sieve();

	for(int i=1;i<P;i++) {
		int bound=sqrt(i)+1;
		for(int j=1;j<bound;j++) {
			if(i%j==0) {
				divisor[i].push_back(j);
				if(i/j!=j)
					divisor[i].push_back(i/j);
			}
		}
	}

	int t;
	cin>>t;
	while(t--) {
		long long l,r;
		cin>>l>>r>>p;

		memset(g[1],0,sizeof(long long)*p);
		memset(f[1],0,sizeof(long long)*p);
		for(int j=1;j<p;j++) {
			f[1][j]=1;
			for(unsigned int i=0;i<divisor[j].size();i++) {
				int d=divisor[j][i];
				g[1][d]++;
			}
		}

		for(int i=2;pow(p,i-1)<=r;i++) {
			memset(g[i],0,sizeof(long long)*p);
			memset(f[i],0,sizeof(long long)*p);

			for(int j=1;j<p;j++) {
				for(unsigned int p=0;p<divisor[j].size();p++) {
					int d=divisor[j][p];
					f[i][j]+=mu[j/d]*g[i-1][j/d];
				}
				for(unsigned int p=0;p<divisor[j].size();p++) {
					int d=divisor[j][p];
					g[i][d]+=f[i][j];
				}
			}
		}

		cout<<calc(r)-calc(l-1)<<endl;
	}

	return 0;
}