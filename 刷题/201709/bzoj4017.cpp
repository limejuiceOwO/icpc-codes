//小Q的无敌异或 按位处理+离散化+树状数组
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define P 998244353LL
#define N 100005
#define NN 262147
#define S 21
using namespace std;

long long xarr[N],sarr[N],pt[N];
long long bit0[NN],bit1[NN];
int pcnt;

long long qur(long long *val,int pos)
{
	pos++;
	long long ans=0;
	while(pos) {
		ans+=val[pos];
		pos-=(pos&-pos);
	}
	return ans;
}

void add(long long *val,int pos)
{
	pos++;
	while(pos<=NN) {
		val[pos]++;
		pos+=(pos&-pos);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		long long x;
		scanf("%lld",&x);
		xarr[i]=x^xarr[i-1];
		sarr[i]=x+sarr[i-1];
	}

	long long ans1=0,ans2=0;
	long long cnt[2];
	for(int s=0;s<S;s++) {
		cnt[0]=cnt[1]=0;
		for(int i=0;i<=n;i++) {
			cnt[(bool)(xarr[i]&(1LL<<s))]++;
		}
		ans1=(ans1+((cnt[0]*cnt[1])<<s))%P;
	}

	for(int s=0;s<2*S;s++) { //注意前缀和位数要乘2
		pcnt=0;
		for(int i=0;i<=n;i++) {
			pt[pcnt++]=sarr[i]&((1LL<<s)-1);
		}
		sort(pt,pt+pcnt);
		pcnt=unique(pt,pt+pcnt)-pt;

		cnt[0]=cnt[1]=0;
		long long cnt2=0;
		memset(bit0,0,sizeof(bit0));
		memset(bit1,0,sizeof(bit1));
		for(int i=0;i<=n;i++) {
			int p=lower_bound(pt,pt+pcnt,sarr[i]&((1LL<<s)-1))-pt;
			if(sarr[i]&(1LL<<s)) { //注意打LL，眼睛是个好东西......
				cnt[1]++;
				add(bit1,p);
				cnt2+=qur(bit0,p)+cnt[1]-qur(bit1,p);
			} else {
				cnt[0]++;
				add(bit0,p);
				cnt2+=cnt[0]-qur(bit0,p)+qur(bit1,p);
			}
		}
		
		if(cnt2&1) {
			ans2|=(1LL<<s);
		}
	}
	printf("%lld %lld\n",ans1,ans2);

	return 0;
}