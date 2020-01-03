#include <iostream>
#include <algorithm>
#define N 10005
using namespace std;

struct LTree {
	int val,dist;
	LTree *l,*r;
} nodes[N],nul;
int cnt=0;
LTree *null=&nul;

LTree *merge(LTree *a,LTree *b)
{
	if(a==null) return b;
	if(b==null) return a;
	if(a->val<b->val) swap(a,b);
	a->r=merge(a->r,b);
	if(a->r->dist>a->l->dist) swap(a->l,a->r);
	a->dist=a->l->dist+1;
	return a;
}

void insert(LTree *&root,int val)
{
	LTree *newnode=nodes+(cnt++);
	newnode->val=val;
	newnode->dist=1;
	newnode->l=newnode->r=null;
	root=merge(newnode,root);
}

void remove(LTree *&root)
{
	root=merge(root->l,root->r);
}

int get(LTree *root)
{
	return root->val;
}
