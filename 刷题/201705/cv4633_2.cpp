//树链剖分练习 LCT实现
#include <cstdio>
#include <algorithm>
#include <vector>
#define N 100005
using namespace std;

struct Splay {
    int val,rev,size;
    long long sum,lazy;
    Splay *ch[2],*fa;
} heap[N];
Splay *null=heap;

vector<int> G[N];
int n;

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

    for(int i=0;i<2;i++) {
        o->ch[i]->sum+=(long long)o->ch[i]->size*o->lazy;
        o->ch[i]->val+=o->lazy;
        o->ch[i]->lazy+=o->lazy;
    }

    o->rev=0;
    o->lazy=0;
}

void maintain(Splay *o)
{
    o->size=o->ch[0]->size+o->ch[1]->size+1;
    o->sum=o->ch[0]->sum+o->ch[1]->sum+o->val;
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

void build(int u=1,int fa=0)
{
    heap[u]=(Splay){0,0,1,0,0,{null,null},&heap[fa]};
    for(unsigned int i=0;i<G[u].size();i++) {
        int v=G[u][i];
        if(v==fa) continue;
        build(v,u);
    }
}

int main()
{
    int m;
    scanf("%d",&n);
    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    build();
    scanf("%d",&m);
    while(m--) {
        int cmd,a,b;
        scanf("%d%d%d",&cmd,&a,&b);
        makeroot(&heap[a]);
        access(&heap[b]);
        if(cmd==2) {
            printf("%lld\n",heap[b].sum);
        } else if(cmd==1) {
            heap[b].lazy+=1;
            heap[b].val+=1;
            heap[b].sum+=heap[b].size;
        }
    }
    return 0;
}