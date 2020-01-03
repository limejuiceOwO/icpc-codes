//CQOI2015 任务查询系统 主席树+离散化
#include <cstdio>
#include <algorithm>
#define N 100005
#define NN 5000005
using namespace std;
//对于size=10^5，节点池大小最少要开修改数量的25倍

struct Node {
	int l,r,cnt;
	long long sum;
} node[NN];
struct Event {
	int t,p;
	bool operator <(const Event &rhs) const {
		return t<rhs.t;
	}
} event[2*N];
int root[N],pt[N];
int n,m,scnt,pcnt,ecnt;
long long pre=1;

long long f(long long a,long long b,long long c)
{
	return (a*pre+b)%c+1;
}

int sig(int x)
{
	return x>0?1:-1;
}

long long qur(long long k,int p,int lb=0,int rb=m)
{
	if(k==0) {
		return 0;
	}
	if(lb==rb) {
		//return node[p].sum;
		return min((long long)node[p].cnt,k)*pt[lb]; //注意每个权值可能出现多次，要返回数量不超过k的部分
	}
	int mid=(lb+rb)>>1;
	if(node[node[p].l].cnt>k) {
		return qur(k,node[p].l,lb,mid);
	} else {
		return qur(k-node[node[p].l].cnt,node[p].r,mid+1,rb)+node[node[p].l].sum;
	}
}

void alt(int pos,long long val,int p,int oldp,int lb=0,int rb=m)
{
	if(lb==rb) {
		//node[p].sum=val;
		node[p].sum=node[oldp].sum+val; //注意要在old的基础上加
		node[p].cnt=node[oldp].cnt+sig(val);
		return;
	}
	int mid=(lb+rb)>>1;
	if(pos>mid) {
		node[p].r=scnt++;
		node[p].l=node[oldp].l;
		alt(pos,val,node[p].r,node[oldp].r,mid+1,rb);
	} else {
		node[p].l=scnt++;
		node[p].r=node[oldp].r;
		alt(pos,val,node[p].l,node[oldp].l,lb,mid);
	}
	node[p].sum=node[node[p].l].sum+node[node[p].r].sum;
	node[p].cnt=node[node[p].l].cnt+node[node[p].r].cnt;
}

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++) {
		int s,e,p;
		scanf("%d%d%d",&s,&e,&p);
		pt[pcnt++]=p;
		event[ecnt++]=(Event) {s,p};
		event[ecnt++]=(Event) {e+1,-p};
	}

	sort(pt,pt+pcnt);
	pcnt=unique(pt,pt+pcnt)-pt;
	sort(event,event+ecnt);

	scnt=1; //注意要保留0节点作为空节点
	for(int i=1,p=0;i<=n+1;i++) {
		root[i]=root[i-1];
		while(p<ecnt&&event[p].t==i) {
			int oldrt=root[i];
			root[i]=scnt++;
			//cout<<"''"<<event[p].p<<" "<<lower_bound(pt,pt+pcnt,abs(event[p].p))-pt<<endl;
			alt(lower_bound(pt,pt+pcnt,abs(event[p].p))-pt,event[p].p,root[i],oldrt);
			p++;
		}
		//for(int z=0;z<scnt;z++) {
		//	cout<<"'"<<z<<" "<<node[z].l<<" "<<node[z].r<<" "<<node[z].cnt<<" "<<node[z].sum<<endl;
		//}
		//cout<<endl;
	}

	for(int i=0;i<n;i++) {
		int x,a,b,c;
		scanf("%d%d%d%d",&x,&a,&b,&c);
		long long k=f(a,b,c);
		//int k,x;
		//cin>>x>>k;
		pre=qur(k,root[x]);
		printf("%lld\n",pre);
	}

	return 0;
}