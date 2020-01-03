#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define N 50005
#define NN 131077
#define LGP 100
using namespace std;

long long n,P,C;
long long val[NN],leaf[N][LGP];
long long phi_table[LGP];
int proc[N];
char lazy[NN],ovf[N],overflow;
int pcnt;

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
		if(k&1) {
			long long t=ans*x;
			if(t>=p) overflow=1;
			ans=t%p;
		}
		x=(x*x)%p;
		k>>=1;
	}
	return ans%p;
}

void build(int l=1,int r=n,int p=1)
{
	if(l==r) {
		cin>>val[p];
		for(int i=0;i<pcnt;i++) {
			leaf[l][i]=val[p]%phi_table[i];
		}
		proc[l]=pcnt;
		if(val[p]>=P) ovf[l]=1;
		val[p]%=P;
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
	if(lazy[p]) return;
	if(lb==rb) {
		for(int i=0;i<proc[lb];i++) {
			long long prev=leaf[lb][i];
			if(ovf[lb]||leaf[lb][0]>=phi_table[i+1]) {
				leaf[lb][i]=qpow(C,leaf[lb][i+1]+phi_table[i+1],phi_table[i]);
			} else {
				leaf[lb][i]=qpow(C,leaf[lb][i+1],phi_table[i]);
			}
			if(!ovf[lb]&&i==0) ovf[lb]=overflow;
			if(i==proc[lb]-1&&prev==leaf[lb][i]) proc[lb]--;
		}
		lazy[p]=(proc[lb]==1);
		val[p]=leaf[lb][0];
	} else {
		int mid=(lb+rb)>>1;
		brute_update(lb,mid,p<<1);
		brute_update(mid+1,rb,p<<1|1);
		val[p]=(val[p<<1]+val[p<<1|1])%P;
		lazy[p]=lazy[p<<1]&&lazy[p<<1|1];
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
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m>>P>>C;
	init_table();
	build();
	while(m--) {
		int cmd,l,r;
		cin>>cmd>>l>>r;
		if(cmd==1) {
			cout<<qur(l,r)<<endl;
		} else if(cmd==0) {
			alt(l,r);
		}
	}
	return 0;
}