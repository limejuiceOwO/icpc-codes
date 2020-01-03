//洞穴探测 LCT模板题x2
#include <cstdio>
#include <algorithm>
#define N 10005
using namespace std;

struct Splay {
	int rev,size;
	Splay *ch[2],*fa;
} heap[N];
Splay *null=heap;

bool isroot(Splay *p)
{
	return p->fa==null||(p->fa->ch[0]!=p&&p->fa->ch[1]!=p);
}

int getd(Splay *o)
{
	return o->fa->ch[1]==o;
}

void pushdown(Splay *o)
{
	if(o->rev) {
		swap(o->ch[0],o->ch[1]);
		o->ch[0]->rev^=1;
		o->ch[1]->rev^=1;
	}
	o->rev=0;
}

void maintain(Splay *o)
{
	o->size=o->ch[0]->size+o->ch[1]->size+1;
	//and more...
}

void rotate(Splay *o) //don`t rotate root node
{
	Splay *p=o->fa,*q=p->fa;
	int d=getd(o),d2=getd(p);

	o->ch[d^1]->fa=p;
	p->ch[d]=o->ch[d^1];

	if(!isroot(p)) q->ch[d2]=o;//notice here
	o->fa=q;

	o->ch[d^1]=p;
	p->fa=o;

	maintain(p);maintain(o);
}

void splay(Splay *u)
{
	static Splay *st[N];
	Splay *p=u;
	int top=0;

	while(!isroot(p)) st[top++]=p,p=p->fa;
	st[top++]=p;

	while(top) {
		p=st[--top];
		pushdown(p);
	}

	while(!isroot(u)) {
		p=u->fa;
		if(!isroot(p)) rotate(getd(u)==getd(p)?p:u);
		rotate(u);
	}
}

void access(Splay *p)
{
	splay(p);
	p->ch[1]=null;
	maintain(p);

	while(p->fa!=null) {
		Splay *q=p->fa;
		splay(q);
		q->ch[1]=p;
		p->fa=q;
		maintain(q);
		splay(p);
	}
}

void makeroot(Splay *p)
{
	access(p);
	p->rev^=1;
}

Splay *findroot(Splay *p)
{
	access(p);
	while(p->ch[0]!=null) p=p->ch[0];
	return p;
}

void cut(Splay *p,Splay *q)
{
	makeroot(p);
	access(q);
	q->ch[0]=p->fa=null;
	maintain(q);
}

void link(Splay *p,Splay *q)
{
	//if(findroot(p)==findroot(q)) return;
	makeroot(q);
	q->fa=p;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);

	for(int i=1;i<=n;i++) {
		heap[i]=(Splay){0,1,{null,null},null};
	}

	while(m--) {
		char cmd[15];
		int u,v;
		scanf("%s%d%d",cmd,&u,&v);
		
		if(cmd[0]=='C') {
			link(heap+u,heap+v);
		} else if(cmd[0]=='Q') {
			printf("%s\n",findroot(heap+u)==findroot(heap+v)?"Yes":"No");
		} else if(cmd[0]=='D') {
			cut(heap+u,heap+v);
		}
	}
}