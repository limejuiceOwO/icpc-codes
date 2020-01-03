#include <iostream>
#include <cstring>
#include <queue>
#define N 1005
#define SIGSIZE 26
using namespace std;

struct Trie {
	int ch[SIGSIZE];
	int fin,last;
} tree[N*N];
int dy[]={0,1,1,1,0,-1,-1,-1},dx[]={-1,-1,0,1,1,1,0,-1};
int ansx[N],ansy[N],wlen[N];
char ansd[N],table[N][N],buf[N];
int n,m;
int cnt=1;

void ins(int idx,char *str)
{
	int p=0,len=strlen(str);
	for(int i=0;i<len;i++) {
		int c=str[i]-'A';
		Trie &cur=tree[p];
		if(!cur.ch[c]) cur.ch[c]=cnt++;
		p=cur.ch[c];
	}
	tree[p].fin=idx;
	wlen[idx]=len-1;
}

void build()
{
	queue<int> q;
	static int f[N*N];
	for(int i=0;i<SIGSIZE;i++) {
		if(tree[0].ch[i]) {
			q.push(tree[0].ch[i]);
		}
	}
	while(!q.empty()) {
		int u=q.front();q.pop();
		int fail=f[u];
		for(int i=0;i<SIGSIZE;i++) {
			int &v=tree[u].ch[i];
			if(!v) {
				v=tree[fail].ch[i];
			} else {
				f[v]=tree[fail].ch[i];
				tree[v].last=tree[f[v]].fin?f[v]:tree[f[v]].last;
				q.push(v);
			}
		}
	}
}

void find(int sx,int sy,int dir)
{
	for(int p=0,i=sx,j=sy;i>=0&&j>=0&&i<n&&j<m;i+=dx[dir],j+=dy[dir]) {
		p=tree[p].ch[table[i][j]-'A'];
		for(int l=(tree[p].fin)?p:(tree[p].last);l;l=tree[l].last) {
			ansx[tree[l].fin]=i-dx[dir]*wlen[tree[l].fin];
			ansy[tree[l].fin]=j-dy[dir]*wlen[tree[l].fin];
			ansd[tree[l].fin]=dir+'A';
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int w;
	cin>>n>>m>>w;
	for(int i=0;i<n;i++) {
		cin>>table[i];
	}
	for(int i=1;i<=w;i++) {
		cin>>buf;
		ins(i,buf);
	}
	build();
	for(int sx=0;sx<n;sx++) {
		find(sx,0,1);
		find(sx,0,2);
		find(sx,0,3);
		find(sx,m-1,5);
		find(sx,m-1,6);
		find(sx,m-1,7);
	}
	for(int sy=0;sy<m;sy++) {
		find(0,sy,3);
		find(0,sy,4);
		find(0,sy,5);
		find(n-1,sy,7);
		find(n-1,sy,0);
		find(n-1,sy,1);
	}
	for(int i=1;i<=w;i++) {
		cout<<ansx[i]<<" "<<ansy[i]<<" "<<ansd[i]<<endl;
	}
	return 0;
}