#include <cstdio>
#include <algorithm>
#define N 4205
using namespace std;

long long f[N],c[2][N];

int main()
{
	int n;
	long long p;
	scanf("%d%lld",&n,&p);

	f[1]=f[2]=1;
	c[0][0]=c[0][2]=1;
	c[0][1]=2%p;
	for(int i=3;i<=n;i++) {
		c[i&1][0]=c[i&1][i]=1;
		for(int j=1;j<i;j++) {
			c[i&1][j]=(c[(i&1)^1][j-1]+c[(i&1)^1][j])%p;
		}

		if(!(i&1)) f[i]=f[i-1];
		for(int j=1;j<i-1;j+=2) {
			f[i]=(f[i]+(f[j]*f[i-j-1]%p)*c[(i&1)^1][j])%p;
		}
	}

	printf("%lld\n",(f[n]*2)%p);
	return 0;
}