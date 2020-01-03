#include <iostream>
#include <algorithm>
#define N 1000005
using namespace std;

struct Treap {
	int key,val;
	Treap *ch[2];
} nodes[N],nul;
Treap *root=&nul,*null=&nul;
int cnt;

void rotate(Treap *&o,int d)
{
	Treap *k=o->ch[d];
	o->ch[d]=k->ch[d^1];k->ch[d^1]=o;o=k;
}

void insert(int val,Treap *&u=root)
{
	if(u==null) {
		u=nodes+(cnt++);
		u->val=val;
		u->key=rand();
		u->ch[0]=u->ch[1]=null;
		return;
	}
	if(u->val==val) return;
	int d=u->val>val?1:0;
	insert(val,u->ch[d]);
	if(u->ch[d]->key>u->key) rotate(u,d);
}

bool find(int val)
{
	Treap *u=root;
	while(u!=null) {
		if(u->val==val) return true;
		u=u->ch[u->val>val];
	}
	return false;
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0,x;i<n;i++) {
		cin>>x;
		insert(x);
	}
	while(m--) {
		int x;
		cin>>x;
		if(find(x)) cout<<"1 ";
		else cout<<"0 ";
	}
	return 0;
}