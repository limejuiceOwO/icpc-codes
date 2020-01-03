//An Enchanted Splay Implemention With Rotation
#include <iostream>
#include <algorithm>
#define N 10005
using namespace std;

struct Splay {
	int val,rev,size;
	Splay *ch[2],*fa;
} heap[N],nul;
Splay *root=&nul,*null=&nul;
int cnt=0;

int getd(Splay *o)
{
	return o->fa->ch[1]==o;
}

void pushdown(Splay *o)
{
	if(o->rev) swap(o->ch[0],o->ch[1]);
	o->ch[0]->rev^=o->rev;o->ch[1]->rev^=o->rev;
	o->rev=0;
}

void maintain(Splay *o)
{
	o->size=o->ch[0]->size+o->ch[1]->size+1;
}

void rotate(Splay *o)
{
	Splay *p=o->fa,*q=p->fa;
	int d=getd(o),d2=getd(p);
	assert(p!=null);
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
	if(u==null) return;
	for(Splay *p;(p=u->fa)!=null;rotate(u)) {
		if(p->fa!=null) {
			pushdown(p);
			rotate(getd(u)==getd(p)?p:u);
		}
	}
	root=u;
}

void push_back(int val)
{
	Splay *u;
	for(u=root;u!=null&&u->ch[1]!=null;u=u->ch[1]) {
		pushdown(u);
		u->size++;
	}
	Splay *np=&heap[cnt++];
	np->val=val;
	np->ch[0]=np->ch[1]=null;
	np->fa=u;
	np->rev=0;
	np->size=1;
	if(root==null) root=np;
	else u->ch[1]=np;
	splay(np);
}

int kth(int k)
{
	Splay *u=root;
	if(k<1||k>root->size) return -1;
	while(u!=null) {
		pushdown(u);
		if(k>u->ch[0]->size) {
			k-=u->ch[0]->size+1;
			if(k<=0) { splay(u); return u->val; }
			u=u->ch[1];
		} else {
			u=u->ch[0];
		}
	}
	return -1;//will never reach there
}

void out(Splay *u=root)
{
	if(u==null) return;
	pushdown(u);
	cout<<"(";
	out(u->ch[0]);
	cout<<")"<<u->val<<"(";
	out(u->ch[1]);
	cout<<")";
	if(u==root) cout<<endl;
}