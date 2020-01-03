#include <cstdio>
//#include <iostream>
#include <algorithm>
#include <set>
#define N 300005
using namespace std;

struct LTree {
	int dist,val,lazy;
	LTree *l,*r,*fa;
	LTree **rev;
} node[N],nul;

LTree *null=&nul;
LTree *pnode[N];
int global;
multiset<int> gmax;

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
	if(a==null) return b;
	if(b==null) return a;
	if(a->val<b->val) swap(a,b);
	pushdown(a);
	a->r=merge(a->r,b);
	a->r->fa=a;
	a->fa=null;
	if(a->l->dist<a->r->dist) swap(a->l,a->r);
	a->dist=a->l->dist+1;
	return a;
}

LTree *update(LTree *u)
{
	LTree *rt=u;
	if(u->fa!=null) rt=update(u->fa);
	pushdown(u);
	return rt;
}

void maintain(LTree *u)
{
	update(u);
	LTree *p=u;
	while(p->fa!=null&&p->val>p->fa->val) {
		swap(p->val,p->fa->val);
		swap(*(p->rev),*(p->fa->rev));
		swap(p->rev,p->fa->rev);
		p=p->fa;
	}
	while(p->val<max(p->l->val,p->r->val)) {
		LTree *mx=((p->l->val)>(p->r->val))?p->l:p->r;
		swap(p->val,mx->val);
		swap(*(p->rev),*(mx->rev));
		swap(p->rev,mx->rev);
		pushdown(p=mx);
	}
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
		node[i].rev=&pnode[i];
		pnode[i]=&node[i];
		gmax.insert(node[i].val);
	}
	scanf("%d",&m);
	while(m--) {
		char cmd[5];
		int x,y;
		scanf("%s",cmd);
		if(cmd[0]=='A') {
			if(cmd[1]=='1') {
				scanf("%d%d",&x,&y);
				LTree *p=update(pnode[x]);
				gmax.erase(gmax.find(p->val));
				pnode[x]->val+=y;
				maintain(pnode[x]);
				gmax.insert(update(pnode[x])->val);
			} else if(cmd[1]=='2') {
				scanf("%d%d",&x,&y);
				LTree *p=update(pnode[x]);
				gmax.erase(gmax.find(p->val));
				p->lazy=y;
				p->val+=y;
				pushdown(p);
				gmax.insert(p->val);
			} else {
				scanf("%d",&y);
				global+=y;
			}
		} else if(cmd[0]=='U') {
			scanf("%d%d",&x,&y);
			LTree *p1=update(pnode[x]),*p2=update(pnode[y]);
			if(p1==p2) continue;
			LTree *k=merge(p1,p2);
			if(k==p1) gmax.erase(gmax.find(p2->val));
			else gmax.erase(gmax.find(p1->val));
		} else if(cmd[0]=='F') {
			if(cmd[1]=='1') {
				scanf("%d",&x);
				update(pnode[x]);
				printf("%d\n",pnode[x]->val+global);
			} else if(cmd[1]=='2') {
				scanf("%d",&x);
				printf("%d\n",update(pnode[x])->val+global);
			} else {
				printf("%d\n",*gmax.rbegin()+global);
			}
		}
	}
	return 0;
}