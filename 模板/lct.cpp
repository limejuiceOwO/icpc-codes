struct Splay {
	int rev,size;
	Splay *ch[2],*fa;
} heap[N];
Splay *null=heap;

bool isroot(Splay *p)
{
	return p->fa==null||(p->fa->ch[0]!=p&&p->fa->ch[1]!=p);
}

int getd(Splay *o)
{
	return o->fa->ch[1]==o;
}

void pushdown(Splay *o)
{
	if(o->rev) {
		swap(o->ch[0],o->ch[1]);
		o->ch[0]->rev^=1;
		o->ch[1]->rev^=1;
	}
	o->rev=0;
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
	static Splay *st[N];
	Splay *p=u;
	int top=0;

	while(!isroot(p)) st[top++]=p,p=p->fa;
	st[top++]=p;

	while(top) {
		p=st[--top];
		pushdown(p);
	}

	while(!isroot(u)) {
		p=u->fa;
		if(!isroot(p)) rotate(getd(u)==getd(p)?p:u);
		rotate(u);
	}
}

void access(Splay *p)
{
	splay(p);
	p->ch[1]=null;
	maintain(p);

	while(p->fa!=null) {
		Splay *q=p->fa;
		splay(q);
		q->ch[1]=p;
		p->fa=q;
		maintain(q);
		splay(p);
	}
}

void makeroot(Splay *p)
{
	access(p);
	p->rev^=1;
}

Splay *findfa(Splay *p)
{
	access(p);
	Splay *ans=p->ch[0];
	while(ans!=null&&ans->ch[1]!=null) ans=ans->ch[1];
	return ans;
}

Splay *findroot(Splay *p)
{
	access(p);
	while(p->ch[0]!=null) p=p->ch[0];
	return p;
}

void cut(Splay *p,Splay *q)
{
	makeroot(p);
	access(q);
	q->ch[0]=p->fa=null;
	maintain(q);
}

void link(Splay *p,Splay *q)
{
	//if(findroot(p)==findroot(q)) return;
	makeroot(q);
	q->fa=p;
}

void build(int u=1,int fa=0)
{
	heap[u]=(Splay){0,1,{null,null},&heap[fa]};
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		build(v,u);
	}
}