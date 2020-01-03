#include <iostream>
#include <algorithm>
#include <cstring>
#define N 10005
using namespace std;

struct Treap {
	int key,val,rank;
	Treap *ch[2];
} nodes[N],nul;
Treap *root=&nul,*null=&nul;
int cnt;

void maintain(Treap *o)
{
	o->rank=o->ch[0]->rank+o->ch[1]->rank+1;
}

void rotate(Treap *&o,int d)
{
	Treap *k=o->ch[d];
	o->ch[d]=k->ch[d^1];k->ch[d^1]=o;o=k;
	maintain(o->ch[d^1]);maintain(o);
}

void insert(int val,Treap *&u=root) //因为需要修改自身，使用引用
{
	if(u==null) {
		u=nodes+(cnt++);
		u->val=val;
		u->key=rand();
		u->rank=1;
		u->ch[0]=u->ch[1]=null;
		return;
	}
	if(u->val==val) return;
	int d=val>u->val?1:0;
	insert(val,u->ch[d]);
	if(u->ch[d]->key>u->key) rotate(u,d);
	maintain(u);
}

bool find(int val)
{
	Treap *u=root;
	while(u!=null) {
		if(u->val==val) return true;
		u=u->ch[val>u->val];
	}
	return false;
}

int kth(int k)
{
	Treap *u=root;
	while(u!=null) {
		if(k>u->ch[0]->rank) {
			k-=u->ch[0]->rank+1;
			if(k==0) return u->val;
			u=u->ch[1];
		} else {
			u=u->ch[0];
		}
	}
	return -1;
}

int main()
{
	while(true) {
		int cmd,val;
		cin>>cmd>>val;
		if(cmd==0) insert(val);
		else if(cmd==1) cout<<kth(val)<<endl;
		else cout<<find(val)<<endl;
	}
	return 0;
}