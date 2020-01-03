//小Z的袜子 莫队算法模板题
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define N 50005
using namespace std;

int n,m,sqn;

int pos(int x) {
	return x/sqn;
}

struct Qur {
	int id,l,r;

	bool operator <(const Qur &rhs) const {
		return pos(l)==pos(rhs.l) ? r<rhs.r : pos(l)<pos(rhs.l);
	}
} qur[N];

int arr[N],cnt[N];
long long cur,ans[N],fm[N];

void mov(int nx,int ny)
{
	static int x=1,y=1;

	if(nx<x) {
		for(int i=x-1;i>=nx;i--)
			cur+=2LL*(cnt[arr[i]]++)+1;
	}

	if(ny>y) {
		for(int i=y+1;i<=ny;i++)
			cur+=2LL*(cnt[arr[i]]++)+1;
	}

	if(nx>x) {
		for(int i=x;i<nx;i++)
			cur-=2LL*(cnt[arr[i]]--)-1;
	}

	if(ny<y) {
		for(int i=y;i>ny;i--)
			cur-=2LL*(cnt[arr[i]]--)-1;
	}

	x=nx,y=ny;
}

long long gcd(long long a,long long b)
{
	while(b>0) {
		long long t=a%b;
		a=b;
		b=t;
	}

	return a;
}

int main()
{
	scanf("%d%d",&n,&m);
	sqn=sqrt(n);

	for(int i=1;i<=n;i++)
		scanf("%d",&arr[i]);

	for(int i=0;i<m;i++) {
		qur[i].id=i;
		scanf("%d%d",&qur[i].l,&qur[i].r);
	}

	sort(qur,qur+m);
	cnt[arr[1]]++;
	cur=1;

	for(int i=0;i<m;i++) {
		int l=qur[i].l,r=qur[i].r;
		ans[qur[i].id]=cur-(r-l+1);
		fm[qur[i].id]=(long long)(r-l+1)*(r-l);
	}

	for(int i=0;i<m;i++) {
		if(ans[i]==0) {
			puts("0/1");
		} else {
			long long g=gcd(ans[i],fm[i]);
			printf("%lld/%lld\n",ans[i]/g,fm[i]/g);
		}
	}

	return 0;
}