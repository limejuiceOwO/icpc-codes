#include <iostream>
#include <algorithm>
using namespace std;

struct LTree {
	int dist,val;
	LTree *fa,*l,*r;
};
LTree heap[N],nul,cnt=0;//initialize nul
LTree *null=&nul;

struct LHeap {
	LTree *root;
	int cnt;
	LHeap() {
		root=&nul;
	}
	LTree* _merge(LTree *a,LTree *b)
	{
		a->fa=b->fa=null;
		if(a==b||a==null) return b;
		if(b==null) return a;
		if(a->val<b->val) swap(a,b);
		a->r=_merge(a->r,b);
		a->r->fa=a;
		if(a->l->dist<a->r->dist) swap(a->l,a->r);
		a->dist=a->l->dist+1;
		return a;
	}
	void merge(const LHeap &rhs)
	{
		root=_merge(root,rhs.root);
	}
	void ins(int val)
	{
		LTree *nnode=heap+(cnt++);
		nnode->l=nnode->r=null;
		nnode->val=val;
		nnode->dist=1;
		root=_merge(root,nnode);
	}
	void del(LTree *u)
	{
		if(u->fa==null) {
			root=merge(u->l,u->r);
			root->fa=null;
		} else {
			LTree *&p=u->fa->l==u?u->fa->l:u->fa->r;
			p=_merge(u->l,u->r);
			p->fa=u;
			u=u->fa;
			if(u->l->dist<u->r->dist) swap(u->l,u->r);
			u->dist=u->l->dist+1;
		}
	}
};