//Usaco2008 轻拍牛头 （并不水的）筛法
#include <cstdio>
#include <algorithm>
#define M 1000005
#define N 100005
using namespace std;

int cnt[M],cnt2[M];
int arr[N];

int main()
{
	int n,mx=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
		cnt2[arr[i]]++;
		mx=max(mx,arr[i]);
	}
	/*
	for(int i=0;i<n;i++) {
		for(int j=2*arr[i];j<=mx;j+=arr[i]) {
			cnt[j]++;
		}
	}
	*/
	//注意以上写法可能会TLE，比如遇到99999个1和1个1000000时......

	for(int i=1;i<=mx;i++) {
		if(!cnt2[i]) continue;
		for(int j=i;j<=mx;j+=i) {
			cnt[j]+=cnt2[i];
		}
	}

	for(int i=0;i<n;i++) {
		printf("%d\n",cnt[arr[i]]-1);
	}

	return 0;
}