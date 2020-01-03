//区间小于P的数目 树状数组离线
#include <cstdio>
#include <algorithm>
#include <vector>
#define N 100005
#define M 100005
using namespace std;

struct P {
	int pos,x;
	bool operator <(const P &rhs) const {
		return x<rhs.x;
	}
} p[N];
struct Qur {
	int k,l,r,p;
	bool operator <(const Qur &rhs) const {
		return p<rhs.p;
	}
} qur[M];

int bit[N],ans[N];
int n;

inline void alter(int pos)
{
	while(pos<=n) {
		bit[pos]++;
		pos+=pos&(-pos);
	}
}

inline int query(int pos)
{
	int ans=0;
	while(pos>0) {
		ans+=bit[pos];
		pos-=pos&(-pos);
	}
	return ans;
}

int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) {
		scanf("%d",&p[i].x);
		p[i].pos=i+1;
	}
	for(int i=0;i<m;i++) {
		qur[i].k=i;
		scanf("%d%d%d",&qur[i].l,&qur[i].r,&qur[i].p);
	}
	sort(p,p+n);
	sort(qur,qur+m);
	int j=0;
	for(int i=0;i<n;i++) {
		while(j<m&&p[j].x<=qur[i].p) alter(p[j++].pos);
		ans[qur[i].k]=query(qur[i].r)-query(qur[i].l-1);
	}
	for(int i=0;i<m;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}