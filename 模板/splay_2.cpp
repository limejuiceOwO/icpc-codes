//An Enchanted Splay Implemention
#include <iostream>
#include <algorithm>
#include <cassert>
#define N 10005
using namespace std;

struct Splay {
	int val,size;
	Splay *ch[2],*fa;
} heap[N];
Splay *root=heap,*null=heap;
int cnt=0;

int getd(Splay *o)
{
	return o->fa->ch[1]==o;
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

	if(!isroot(p)) q->ch[d2]=o;
	o->fa=q;

	o->ch[d^1]=p;
	p->fa=o;

	maintain(p);maintain(o);
}

void splay(Splay *u)
{
	if(u==null) return;

	for(Splay *p;(p=u->fa)!=null;rotate(u)) {
		if(p->fa!=null) rotate(getd(u)==getd(p)?p:u);
	}

	root=u;
}

void ins(int val)
{
	Splay *u,*fa;

	for(u=root,fa=null;u!=null&&u->val!=val;fa=u,u=u->ch[val>u->val]);

	if(u==null) {
		Splay *np=&heap[cnt++];
		*np=(Splay) {val,1,{null,null},fa};
		if(root==null) root=np;
		else fa->ch[val>fa->val]=np;
		splay(np);
	}
}
/*
void out(Splay *u=root)
{
	if(u==null) return;
	cout<<"(";
	out(u->ch[0]);
	cout<<")"<<u->val<<"(";
	out(u->ch[1]);
	cout<<")";
	if(u==root) cout<<endl;
}
*/