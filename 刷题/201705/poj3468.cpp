//Splay 区间修改/查询(TLE)
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#define N 200005
using namespace std;

struct Splay {
	long long val,sum,lazy,size;
	Splay *ch[2],*fa;
} heap[N];

Splay *root,*null=heap;
int n;

void pushdown(Splay *u)
{
	Splay *st[N];
	int top=0;

	while(u!=root) st[top++]=u,u=u->fa;
	st[top++]=u;

	while(top) {
		Splay *p=st[--top];
		for(int i=0;i<2;i++) {
			p->ch[i]->val+=p->lazy;
			p->ch[i]->sum+=p->lazy*p->ch[i]->size;
			p->ch[i]->lazy+=p->lazy;
		}
		p->lazy=0;
	}
}

void maintain(Splay *u)
{
	u->sum=u->ch[0]->sum+u->ch[1]->sum+u->val;
	u->size=u->ch[0]->size+u->ch[1]->size+1;
}

int getd(Splay *u)
{
	return u->fa->ch[1]==u;
}

void rotate(Splay *u)
{
	Splay *p=u->fa,*q=p->fa;
	int d=getd(u),d2=getd(p);
	u->ch[d^1]->fa=p;
	p->ch[d]=u->ch[d^1];
	u->ch[d^1]=p;
	p->fa=u;
	q->ch[d2]=u;//may change null
	u->fa=q;
	maintain(p);maintain(u);
}

void splay(Splay *u)
{
	pushdown(u);
	for(Splay *p;(p=u->fa)!=null;rotate(u)) {
		if(p->fa!=null) rotate(getd(u)==getd(p)?p:u);
	}
	root=u;
}

long long qur(int pos)
{
	if(pos<=0) return 0;
	if(pos>=n) {
		splay(&heap[n]);
		return root->sum;
	}
	splay(&heap[pos+1]);
	return root->ch[0]->sum;
}

void alt(int pos,long long val)
{
	if(pos<=0) return;
	if(pos>=n) {
		splay(&heap[n]);
		root->lazy+=val;
		root->sum+=val*root->size;
		root->val+=val;
		return;
	}
	splay(&heap[pos+1]);
	root->ch[0]->lazy+=val;
	root->ch[0]->sum+=val*root->ch[0]->size;
	root->ch[0]->val+=val;
	maintain(root);
}

int main()
{
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		int v;
		cin>>v;
		heap[i]=(Splay){v,0,0,0,{&heap[i-1],null},&heap[i+1]};
		maintain(&heap[i]);
	}
	heap[n].fa=null;
	root=&heap[n];
	while(m--) {
		char cmd[5];
		int l,r,v;
		cin>>cmd>>l>>r;
		if(cmd[0]=='Q') {
			cout<<qur(r)-qur(l-1)<<endl;
		} else if(cmd[0]=='C') {
			cin>>v;
			alt(l-1,-v);
			alt(r,v);
		}
	}
	return 0;
}