#include <cstdio>
#include <algorithm>
#define N 100005
#define BLKSIZE 1005
#define FIRST 3005
using namespace std;

double arr[N],seg[N/BLKSIZE+5];

int main()
{
	int n;
	double a;
	scanf("%d%lf",&n,&a);

	int p=1;
	for(int i=1;i<=n;i++) {
		scanf("%lf",&arr[i]);

		double ans=0;
		if(p<=a*i) {
			seg[p/BLKSIZE]+=arr[p];
			p++;
		}

		int j;
		for(j=1;j+BLKSIZE<p-FIRST;j+=BLKSIZE) {
			ans+=seg[j/BLKSIZE]/(i-j);
		}
		for(;j<p;j++) {
			ans+=arr[j]/(i-j);
		}
		printf("%.6lf",ans*arr[i]);
	}

	return 0;
}