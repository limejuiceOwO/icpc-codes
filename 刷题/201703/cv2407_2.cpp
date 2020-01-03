#include <cstdio>
#include <iostream>
#include <algorithm>
#define N 300005
using namespace std;

struct LTree {
	int dist,val,lazy;
	LTree *l,*r,*fa;
} node[N],gnode[N],nul;

LTree *null=&nul,*groot=&nul;
int global=0;

void pushdown(LTree *u)
{
	if(u->l!=null) {
		u->l->val+=u->lazy;
		u->l->lazy+=u->lazy;
	}
	if(u->r!=null) {
		u->r->val+=u->lazy;
		u->r->lazy+=u->lazy;
	}
	u->lazy=0;
}

LTree *merge(LTree *a,LTree *b)
{
	if(a==null||a==b) {
		b->fa=null;
		return b;
	}
	if(b==null) {
		a->fa=null;
		return a;
	}
	if(a->val<b->val) swap(a,b);
	pushdown(a);
	a->r=merge(a->r,b);
	a->r->fa=a;
	a->fa=null;
	if(a->l->dist<a->r->dist) swap(a->l,a->r);
	a->dist=a->l->dist+1;
	return a;
}

LTree *rt(LTree *u)
{
	LTree *root=u->fa==null?u:rt(u->fa);
	pushdown(u);
	return root;
}

LTree *rm(LTree *u,LTree *oldrt=0)
{
	LTree *fa=u->fa,*ret;
	if(fa==null) {
		ret=merge(u->l,u->r);
	} else {
		LTree *&p=fa->l==u?fa->l:fa->r;
		p=merge(u->l,u->r);
		p->fa=fa;
		if(fa->l->dist<fa->r->dist) swap(fa->l,fa->r);
		fa->dist=fa->l->dist+1;
		ret=oldrt;
	}
	u->l=u->r=u->fa=null;
	u->dist=1;
	return ret;
}

int main()
{
	int n,m;
	scanf("%d",&n);
	nul.val=-1000000;
	for(int i=1;i<=n;i++) {
		scanf("%d",&node[i].val);
		node[i].l=node[i].r=node[i].fa=null;
		node[i].lazy=0;
		node[i].dist=1;
		gnode[i]=node[i];
		groot=merge(groot,&gnode[i]);
	}
	scanf("%d",&m);
	while(m--) {
		char cmd[5];
		int x,y;
		scanf("%s",cmd);
		if(cmd[0]=='A') {
			if(cmd[1]=='1') {
				scanf("%d%d",&x,&y);
				LTree *root=rt(&node[x]);
				groot=rm(&gnode[root-node],groot);
				root=rm(&node[x],root);
				node[x].val+=y;
				root=merge(root,&node[x]);
				gnode[x].val=node[x].val;
				gnode[root-node].val=root->val;
				groot=merge(&gnode[root-node],groot);
			} else if(cmd[1]=='2') {
				scanf("%d%d",&x,&y);
				LTree *root=rt(&node[x]);
				root->lazy=y;
				root->val+=y;
				groot=rm(&gnode[root-node],groot);
				gnode[root-node].val=root->val;
				groot=merge(groot,&gnode[root-node]);
			} else {
				scanf("%d",&y);
				global+=y;
			}
		} else if(cmd[0]=='U') {
			scanf("%d%d",&x,&y);
			LTree *root1=rt(&node[x]),*root2=rt(&node[y]);
			if(root1==root2) continue;
			LTree *newroot=merge(root1,root2);
			if(newroot==root1) groot=rm(&gnode[root2-node],groot);
			else groot=rm(&gnode[root1-node],groot);
		} else if(cmd[0]=='F') {
			if(cmd[1]=='1') {
				scanf("%d",&x);
				rt(&node[x]);
				printf("%d\n",node[x].val+global);
			} else if(cmd[1]=='2') {
				scanf("%d",&x);
				printf("%d\n",rt(&node[x])->val+global);
			} else {
				printf("%d\n",groot->val+global);
			}
		}
	}
	return 0;
}