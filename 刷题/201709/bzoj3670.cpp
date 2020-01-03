#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 1000005
#define P 1000000007LL
using namespace std;

int nxt[N],nxt2[N],cnt[N],num[N];
char str[N];

int main()
{
	int t;
	scanf("%d",&t);
	while(t--) {
		scanf("%s",str);
		int len=strlen(str);

		long long ans=1;
		for(int i=0,j;i<len-1;i++) {
			j=nxt[i];
			while(j&&str[i+1]!=str[j])
				j=nxt[j-1];
			nxt[i+1]=(str[i+1]==str[j] ? j+1 : 0);
			cnt[i+1]=nxt[i+1]==0 ? 0 : cnt[nxt[i+1]-1]+1;
			j=nxt2[i];
			while(j&&(j+1>(i+2)/2||str[i+1]!=str[j]))
				j=nxt[j-1];
			nxt2[i+1]=(str[i+1]==str[j] ? j+1 : 0);
			num[i+1]=nxt2[i+1]==0 ? 0 : cnt[nxt2[i+1]-1]+1;
			ans=ans*(num[i+1]+1)%P;
		}

		printf("%lld\n",ans);
	}

	return 0;
}