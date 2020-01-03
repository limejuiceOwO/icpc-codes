#include <iostream>
#include <algorithm>
#include <stack>
#define N 1000005
using namespace std;

struct Blk {
	long long a,b;
	long long h;
	Blk *prev,*next;
} blk[N],nul;
Blk *null=&nul;

void merge(Blk *a,Blk *b,long long delta)
{
	//f'(x)=f(x+delta)-f(delta)+g(x),c=0
	a->b=2*a->a*delta+a->b+b->b;
	a->a=a->a+b->a;

	if(a->prev==b) {
		b->prev->next=a;
		a->prev=b->prev;
	} else {
		b->next->prev=a;
		a->next=b->next;
	}
}

long long f(Blk *bk,long long p)
{
	return p*(bk->b+p*bk->a);
}

long long mnx(Blk *bk,long long k)
{
	long long p=-(bk->b-k)/(2*bk->a);
	long long ans=p;
	if(f(bk,ans)-k*ans>f(bk,p+1)-k*(p+1))
		ans=p+1;
	if(f(bk,ans)-k*ans>f(bk,p-1)-k*(p-1))
		ans=p-1;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	int n,c;
	cin>>n>>c;

	blk[0].prev=blk[0].next=null;
	nul.h=100000005;
	for(int i=0;i<n;i++) {
		cin>>blk[i].h;
		blk[i].a=1;
		if(i) {
			blk[i].prev=&blk[i-1];
			blk[i-1].next=&blk[i];
			blk[i].next=null;
		}
	}

	stack<int> mark;
	long long ans=0;
	for(int i=1;i<n;i++) {
		ans+=c*abs(blk[i].h-blk[i-1].h);
	}
	for(Blk *p=blk;p!=null;p=p->next) {
		while(p->h==p->next->h) {
			merge(p,p->next,0);
		}
		if(p->prev->h>p->h&&p->next->h>p->h) {
			mark.push(p-blk);
		}
	}

	while(!mark.empty()) {
		int i=mark.top();mark.pop();
		if(blk[i].prev==null&&blk[i].next==null) break;
		//cout<<" "<<i<<endl;

		long long delta=min(blk[i].prev->h,blk[i].next->h)-blk[i].h;
		long long side=2-(blk[i].prev==null||blk[i].next==null);

		long long v=mnx(&blk[i],side*c);
		long long m=min(delta,v);
		if(v<=0) continue;
		blk[i].h+=m;
		ans+=f(&blk[i],m)-side*c*m;
		if(v>delta) {
			long long ph=delta;
			if(blk[i].next->h==blk[i].h) {
				merge(&blk[i],blk[i].next,ph);
				ph=0;
			}
			if(blk[i].prev->h==blk[i].h) {
				merge(&blk[i],blk[i].prev,ph);
				ph=0;
			}
			if(blk[i].prev->h>blk[i].h&&blk[i].next->h>blk[i].h) {
				mark.push(i);
			}
		}
	}

	cout<<ans<<endl;
	return 0;
}