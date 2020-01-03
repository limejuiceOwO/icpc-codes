//Splay Implemention Final Version(?)
#include <iostream>
#include <algorithm>
#define N 1005
using namespace std;

struct Splay {
	int ch[2],fa;
	int sz,val;
} tree[N];
int root,scnt; //root=0,scnt=1

int cp(int p)
{
	return tree[tree[p].fa].val<tree[p].val;
}

void pushup(int p)
{
	tree[p].sz=tree[tree[p].ch[0]].sz+tree[tree[p].ch[1]].sz+1;
}

void rot(int p)
{
	int p1=tree[p].fa,p2=tree[p1].fa;
	int d1=cp(p),d2=cp(p1);
	tree[p1].ch[d1]=tree[p].ch[d1^1];
	tree[tree[p].ch[d1^1]].fa=p1;
	tree[p].ch[d1^1]=p1;
	tree[p1].fa=p;
	if(p2)
		tree[p2].ch[d2]=p;
	else
		root=p;
	tree[p].fa=p2;
	pushup(p1);
	pushup(p);
}

void splay(int p)
{
	for(int pp;(pp=(tree[p].fa));rot(p)) {
		if(tree[pp].fa) {
			rot(cp(p)==cp(pp) ? pp : p);
		}
	}
}

void ins(int v,int f=0,int &p=root)
{
	if(!p) {
		p=scnt;
		tree[scnt]=(Splay) {{0,0},f,1,v};
		splay(scnt++);
		return;
	}
	int d=tree[p].val<v;
	ins(v,p,tree[p].ch[d]);
}

bool qur(int v)
{
	int p=root;
	while(p) {
		if(tree[p].val==v) {
			splay(p);
			return true;
		}
		int d=tree[p].val<v;
		p=tree[p].ch[d];
	}
	return false;
}

int kth(int k)
{
	int p=root;
	while(p) {
		if(k>tree[tree[p].ch[0]].sz) {
			k-=tree[tree[p].ch[0]].sz+1;
			if(k<=0) {
				splay(p);
				return tree[p].val;
			}
			p=tree[p].ch[1];
		} else {
			p=tree[p].ch[0];
		}
	}
	return -1;
}

void del(int v)
{
	if(!qur(v)) return;
	int ls=tree[root].ch[0],rs=tree[root].ch[1];
	tree[ls].fa=0;root=ls;
	while(tree[ls].ch[1]) ls=tree[ls].ch[1];
	splay(ls);
	tree[rs].fa=ls;tree[ls].ch[1]=rs;
}

int prefix(int v,int p=root)
{
	if(!p) return -1;
	if(tree[p].val<v) {
		int r=prefix(v,tree[p].ch[1]);
		return r>=0 ? r : tree[p].val;
	} else {
		return prefix(v,tree[p].ch[0]);
	}
}

int suffix(int v,int p=root)
{
	if(!p) return -1;
	if(tree[p].val>v) {
		int r=suffix(v,tree[p].ch[0]);
		return r>=0 ? r : tree[p].val;
	} else {
		return suffix(v,tree[p].ch[1]);
	}
}

void out(int p=root)
{
	if(!p) return;
	cout<<"(";
	out(tree[p].ch[0]);
	cout<<")"<<tree[p].val<<","<<tree[p].sz<<"(";
	out(tree[p].ch[1]);
	cout<<")";
	if(p==root) cout<<endl;
}

int main()
{
	scnt=1;
	ins(2);
	ins(4);
	ins(1);
	out();
	del(2);
	out();
	return 0;
}