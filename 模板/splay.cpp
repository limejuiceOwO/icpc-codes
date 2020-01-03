struct Splay {
	int val,rank,cnt;
	Splay *ch[2];
} nodes[N],nul;
Splay *null=&nul,*root=&nul;
int cnt;

void maintain(Splay *o)
{
	o->rank=o->ch[0]->rank+o->ch[1]->rank+o->cnt;
}

void rotate(Splay *&o,int d)
{
	Splay *k=o->ch[d];
	o->ch[d]=k->ch[d^1];k->ch[d^1]=o;o=k;
	maintain(o->ch[d^1]);maintain(o);
}

int out(Splay *u=root)
{
	int maxd=-1;
	if(u==null) return 0;
	cout<<"(";
	maxd=max(maxd,out(u->ch[0]));
	cout<<")"<<u->val<<"(";
	maxd=max(maxd,out(u->ch[1]));
	cout<<")";
	if(u==root) cout<<endl;
	return maxd+1;
}

bool splay(int val,Splay *&u=root)//and find
{
	if(u==null) return false;
	if(u->val==val) return true;
	int d=val>u->val?1:0;
	Splay *&p=u->ch[d];
	if(p==null) return false;
	if(p->val!=val) {
		int d2=val>p->val?1:0;
		if(!splay(val,p->ch[d2])) return false;
		if(d==d2) rotate(u,d);
		else rotate(p,d2);
	}
	rotate(u,d);
	return true;
}

void insert(int val,Splay *&u=root)
{
	if(u==null) {
		u=nodes+(cnt++);
		u->val=val;
		u->rank=u->cnt=1;
		u->ch[0]=u->ch[1]=null;
		return;
	} else if(u->val==val) {
		u->rank++;u->cnt++;
		return;
	}
	insert(val,u->ch[val>u->val]);
	maintain(u);
}

void _del(Splay *&u)
{
	if(u->ch[0]!=null&&u->ch[1]!=null) {
		int d=u->ch[0]->rank<u->ch[1]->rank?0:1;
		rotate(u,d);
		_del(u->ch[d^1]);
		maintain(u);
		return;
	}
	if(u->ch[0]==null) u=u->ch[1];
	else u=u->ch[0];
}

void del(int val,Splay *&u=root)
{
	if(u==null) return;
	if(val==u->val) {
		if(u->cnt>1) {
			u->cnt--;u->rank--;
		} else _del(u);
	} else {
		del(val,u->ch[val>u->val]);
		maintain(u);
	}
}

int kth(int k)
{
	Splay *u=root;
	while(u!=null) {
		if(k>u->ch[0]->rank) {
			k-=u->ch[0]->rank+u->cnt;
			if(k<=0) { splay(u->val); return u->val; }
			u=u->ch[1];
		} else {
			u=u->ch[0];
		}
	}
	return -1;
}

void del2(int val)//an splay-based alternative implemention of del(x)
{
	if(!splay(val)) return;
	if(root->cnt>1) {
		root->cnt--;
		return;
	} 
	Splay *cr=root->ch[1];
	if(root->ch[0]!=null) {
		root=root->ch[0];
		splay(kth(root->rank));
		root->ch[1]=cr;
		maintain(root);
	} else {
		root=root->ch[1];
	}
}

int rank(int val)
{
	if(splay(val)) return root->ch[0]->rank+1;
	return -1;
}

int prefix(int val,Splay *u=root)
{
	if(u==null) return val;//not found
	if(val>u->val) {
		int s=prefix(val,u->ch[1]);
		if(s==val) return u->val;
		return s;
	} else {
		return prefix(val,u->ch[0]);
	}
}

int suffix(int val,Splay *u=root)
{
	if(u==null) return val;//not found
	if(val<u->val) {
		int s=suffix(val,u->ch[0]);
		if(s==val) return u->val;
		return s;
	} else {
		return suffix(val,u->ch[1]);
	}
}