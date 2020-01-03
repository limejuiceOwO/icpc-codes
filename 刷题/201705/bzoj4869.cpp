#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define N 50005
#define NN 131077
#define LGP 100
using namespace std;

long long P,C;
long long val[NN],leaf[N][LGP],src[N];
long long phi_table[LGP];
char lazy[NN],ovf[N],overflow;
int n,pcnt;

inline long long phi(long long x)
{
	long long ans=x;
	long long z=ceil(sqrt(x));
	for(int i=2;i<=z;i++) {
		if(x%i==0) {
			ans*=(i-1);
			ans/=i;
			while(x%i==0) x/=i;
		}
	}
	if(x>1) {
		ans*=x-1;
		ans/=x;
	}
	return ans;
}

inline long long qpow(long long x,long long k,long long p)
{
	long long ans=1;
	overflow=0;
	while(k) {
		if(x>=p) overflow=1; //注意顺序，这句放到循环末尾是错的（ans有可能没乘x*x）
		x=x%p;
		if(k&1) {
			ans=ans*x;
			if(ans>=p) overflow=1; //注意要判两次(注掉似乎也能A...)
			ans%=p;
		}
		x=x*x;
		k>>=1;
	}
	return ans%p;
}

void build(int l=1,int r=n,int p=1)
{
	if(l==r) {
		//cin>>val[p];
		scanf("%lld",&val[p]);
		for(int i=0;i<pcnt;i++) {
			leaf[l][i]=val[p]%phi_table[i];
		}
		//if(val[p]>=P) ovf[l]=1;
		//val[p]%=P;
		src[l]=val[p];
	} else {
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		val[p]=(val[p<<1]+val[p<<1|1])%P;
	}
	//lazy[p]=0;
}

void brute_update(int lb,int rb,int p)
{
	static long long prev[LGP];
	if(lazy[p]) return;
	if(lb==rb) {
		memcpy(prev,leaf[lb],sizeof(long long)*pcnt); //注意全部比较一遍
		for(int i=0;i<pcnt;i++) {
			if(ovf[lb]||src[lb]>=phi_table[i+1]) {
				leaf[lb][i]=qpow(C,leaf[lb][i+1]+phi_table[i+1],phi_table[i]);
			} else {
				leaf[lb][i]=qpow(C,leaf[lb][i+1],phi_table[i]);
			}
		}
		if(!ovf[lb]) { //注意最后再更新ovf标记
			src[lb]=qpow(C,src[lb],P);
			ovf[lb]=overflow;
		}
		val[p]=leaf[lb][0];
		if(!memcmp(prev,leaf[lb],sizeof(long long)*pcnt)) lazy[p]=1;
	} else {
		int mid=(lb+rb)>>1;
		brute_update(lb,mid,p<<1);
		brute_update(mid+1,rb,p<<1|1);
		val[p]=(val[p<<1]+val[p<<1|1])%P;
		lazy[p]=lazy[p<<1]&&lazy[p<<1|1]; //上传lazy
	}
}

long long qur(int l,int r,int lb=1,int rb=n,int p=1)
{
	if(l<=lb&&r>=rb) {
		return val[p];
	}
	if(l>rb||r<lb) {
		return 0;
	}
	int mid=(lb+rb)>>1;
	return (qur(l,r,lb,mid,p<<1)+qur(l,r,mid+1,rb,p<<1|1))%P;
}

void alt(int l,int r,int lb=1,int rb=n,int p=1)
{
	if(l<=lb&&r>=rb) {
		brute_update(lb,rb,p);
		return;
	}
	if(l>rb||r<lb) {
		return;
	}
	int mid=(lb+rb)>>1;
	alt(l,r,lb,mid,p<<1);
	alt(l,r,mid+1,rb,p<<1|1);
	val[p]=(val[p<<1]+val[p<<1|1])%P;
}

void init_table()
{
	pcnt=0;
	long long eul=P;
	while(eul>1) {
		phi_table[pcnt++]=eul;
		eul=phi(eul);
	}
	phi_table[pcnt]=1;//只是为了省个特判orz
}

int main()
{
	//ios::sync_with_stdio(false);
	int m;
	//cin>>n>>m>>P>>C;
	scanf("%d%d%lld%lld",&n,&m,&P,&C);
	init_table();
	build();
	while(m--) {
		int cmd,l,r;
		//cin>>cmd>>l>>r;
		scanf("%d%d%d",&cmd,&l,&r);
		if(cmd==1) {
			//cout<<qur(l,r)<<endl;
			printf("%lld\n",qur(l,r));
		} else if(cmd==0) {
			alt(l,r);
		}
	}
	return 0;
}