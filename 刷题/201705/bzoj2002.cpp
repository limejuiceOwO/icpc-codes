//弹飞绵羊 LCT模板题
#include <cstdio>
#include <algorithm>
#define N 200005
using namespace std;

struct Splay {
	int rev,size;
	Splay *ch[2],*fa,*pre;
} heap[N],nul;
Splay *null=heap;

int n;

int getd(Splay *o)
{
	return o->fa->ch[1]==o;
}

void pushdown(Splay *o)
{
	for(int i=0;i<2;i++) {
		if(o->rev) swap(o->ch[i]->ch[0],o->ch[i]->ch[1]);
		o->ch[i]->rev^=o->rev;
	}
	o->rev=0;
}

void maintain(Splay *o)
{
	o->size=o->ch[0]->size+o->ch[1]->size+1;
	//and more...
}

void rotate(Splay *o)
{
	Splay *p=o->fa,*q=p->fa;
	int d=getd(o),d2=getd(p);
	o->ch[d^1]->fa=p;
	p->ch[d]=o->ch[d^1];
	o->ch[d^1]=p;
	p->fa=o;
	q->ch[d2]=o;//may change null
	o->fa=q;
	maintain(p);maintain(o);
}

void splay(Splay *u)
{
	Splay *p=u;
	static Splay *st[N];
	int top=0;
	while(p->fa!=null) st[top++]=p,p=p->fa;
	u->pre=p->pre;
	while(top) {
		p=st[--top];
		pushdown(p);
	}
	for(;(p=u->fa)!=null;rotate(u)) {
		if(p->fa!=null) rotate(getd(u)==getd(p)?p:u);
	}
}

void reverse(Splay *p)
{
	p->rev^=1;
	swap(p->ch[0],p->ch[1]);
}

void cutright(Splay *p)
{
	if(p->ch[1]!=null) {
		p->ch[1]->pre=p;
		p->ch[1]->fa=null;
		p->ch[1]=null;
	}
	maintain(p);
}

void access(Splay *p)
{
	splay(p);cutright(p);
	while(p->pre!=null) {
		Splay *q=p->pre;
		splay(q);
		cutright(q);
		q->ch[1]=p;
		p->fa=q;
		p->pre=null;
		maintain(q);
		splay(p);
	}
}

int main()
{
	int m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		int v;
		scanf("%d",&v);
		heap[i]=(Splay){0,1,{null,null},null,&heap[min(i+v,n+1)]};
	}
	heap[n+1]=(Splay){0,1,{null,null},null,null};
	scanf("%d",&m);
	while(m--) {
		int cmd,a,b;
		scanf("%d%d",&cmd,&a);
		a++;
		if(cmd==1) {
			access(&heap[a]);
			printf("%d\n",heap[a].ch[0]->size);
		} else if(cmd==2) {
			scanf("%d",&b);
			access(&heap[a]);
			heap[a].ch[0]->fa=heap[a].ch[0]->pre=null;
			heap[a].ch[0]=null;
			heap[a].pre=&heap[min(a+b,n+1)];
			maintain(&heap[a]);
		}
		//out();
	}
	return 0;
}