#include <iostream>
#include <algorithm>
#define N 1005
using namespace std;

struct Tree {
	int key;
	Tree *ch[2];
}heap[N],nul;
Tree *null=&nul,*root=&nul;
Tree *st[N];
int top=0,cnt=0;

void insert(int key)
{
	while(top&&st[top-1]->key>key) top--;
	heap[cnt].ch[0]=st[top];
	heap[cnt].ch[1]=null;
	heap[cnt].key=key;
	if(top) st[top-1]->ch[1]=heap+cnt;
	else root=heap+cnt;
	st[top++]=heap+(cnt++);
	st[top]=null;
}

void walk(Tree *p,int d)
{
	if(p==null) return;
	walk(p->ch[0],d+1);
	cout<<"("<<d<<","<<p->key<<") ";
	walk(p->ch[1],d+1);
}

int main()
{
	int n;
	cin>>n;
	st[0]=null;
	for(int i=0,x;i<n;i++) {
		cin>>x;
		insert(x);
	}
	walk(root,1);
	return 0;
}