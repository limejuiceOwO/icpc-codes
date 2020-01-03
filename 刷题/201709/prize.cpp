#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define N 15
#define INF 1000005
using namespace std;

struct Node {
	Node *ch[4],*fail;
	unsigned int w;
} trie[N*100];

struct Stat {
	Node *u;
	int d;
	unsigned int w;
};

int cost[N];
int mem[2][N*100][1029];
int cnt,ans;

void ins(const string &s,int id)
{
	unsigned int pos=0;
	Node *p=trie;
	while(pos<s.length()) {
		if(!p->ch[s[pos]-'a']) {
			p->ch[s[pos]-'a']=trie+(++cnt);
		}
		p=p->ch[s[pos]-'a'];
		pos++;
	}
	p->w|=(1<<id);
}

void build()
{
	queue<Node*> que;

	trie->fail=trie;
	for(int i=0;i<4;i++) {
		if(trie->ch[i]) {
			trie->ch[i]->fail=trie;
			que.push(trie->ch[i]);
		} else {
			trie->ch[i]=trie;
		}
	}

	while(!que.empty()) {
		Node *p=que.front();que.pop();
		for(int i=0;i<4;i++) {
			if(p->ch[i]) {
				p->w|=p->fail->w;
				p->ch[i]->fail=p->fail->ch[i];
				que.push(p->ch[i]);
			} else {
				p->ch[i]=p->fail->ch[i];
			}
		}
	}
}

void update(int &a,int b)
{
	a=max(a,b);
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		string s;
		cin>>s>>cost[i];
		ins(s,i);
	}

	build();
	
	//bfs(?)
	queue<Stat> que;
	que.push((Stat) {trie,0,0});
	int lvl=0;
	ans=-INF;
	memset(mem[1],0x80,sizeof(mem[0]));
	while(!que.empty()) {
		Stat cur=que.front();que.pop();
		Node *u=cur.u;
		if(cur.d==m) {
			ans=max(ans,mem[lvl&1][u-trie][cur.w]);
			continue;
		}
		if(cur.d>lvl) {
			memset(mem[lvl&1],0x80,sizeof(mem[0]));
			lvl++;
		}
		for(int i=0;i<4;i++) {
			int mask=(~cur.w)&u->ch[i]->w;
			int ncost=mem[lvl&1][u-trie][cur.w];
			for(int i=0;i<n;i++) {
				if(mask&(1<<i)) ncost+=cost[i];
			}
			if(mem[(lvl&1)^1][u->ch[i]-trie][cur.w|u->ch[i]->w]<=-INF) {
				que.push((Stat) {u->ch[i],cur.d+1,cur.w|u->ch[i]->w});
			}
			update(mem[(lvl&1)^1][u->ch[i]-trie][cur.w|u->ch[i]->w],ncost);
		}
	}

	if(ans>=0)
		cout<<ans<<endl;
	else
		cout<<"Unhappy!"<<endl;
	return 0;
}