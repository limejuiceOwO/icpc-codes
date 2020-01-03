//NOIP2012 借教室 线段树模拟
#include <cstdio>
#include <algorithm>
#define NN 1048581
#define INF 1000000005
using namespace std;

struct LTree {
	int lb,rb,lazy,val;
} t[NN];
//int lb[NN],rb[NN],val[NN],lazy[NN];
int n;
int l,r,v;

inline int min(int a,int b)
{
	return a>b?b:a;
}

void build(int l=1,int r=n,int p=1)
{
	if(l>=r) {
		scanf("%d",&t[p].val);
	} else {
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		t[p].val=min(t[p<<1].val,t[p<<1|1].val);
	}
	t[p].lb=l;
	t[p].rb=r;
	//t[p].lazy=0;
}

inline void pushdown(int p)
{
	if(t[p].lazy) {
		t[p<<1].lazy+=t[p].lazy;
		t[p<<1|1].lazy+=t[p].lazy;
		t[p<<1].val+=t[p].lazy;
		t[p<<1|1].val+=t[p].lazy;
		t[p].lazy=0;
	}
}

int qur(int p=1)
{
	if(l<=t[p].lb&&r>=t[p].rb) return t[p].val;
	if(l>t[p].rb||r<t[p].lb) return INF;
	pushdown(p);
	return min(qur(p<<1),qur(p<<1|1));
}

void alt(int p=1)
{
	//cout<<p<<" "<<t[p].lb<<" "<<t[p].rb<<endl;
	if(l<=t[p].lb&&r>=t[p].rb) {
		t[p].val+=v;
		t[p].lazy+=v;
		return;
	}
	if(l>t[p].rb||r<t[p].lb) return;
	pushdown(p);
	alt(p<<1);
	alt(p<<1|1);
	t[p].val=min(t[p<<1].val,t[p<<1|1].val);
}
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	build();
	for(int i=1;i<=m;i++) {
		int d,s,t;
		scanf("%d%d%d",&d,&s,&t);
		l=s,r=t,v=-d;
		alt();
		//cout<<"A:"<<endl;
		if(qur()<0) {
			printf("-1\n%d\n",i);
			return 0;
		}
	}
	puts("0");
	return 0;
}