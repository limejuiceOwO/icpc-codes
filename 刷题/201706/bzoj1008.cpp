#include <cstdio>
#include <algorithm>
#define P 100003
using namespace std;

long long qpow(long long x,long long k)
{
	long long ret=1;
	while(k) {
		if(k&1) ret=(ret*x)%P;
		x=(x*x)%P;
		k>>=1;
	}

	return ret;
}

int main()
{
	long long n,m;
	scanf("%lld%lld",&m,&n);
	printf("%lld\n",(qpow(m,n)-qpow(m-1,n-1)*m%P+P)%P);
	return 0;
}