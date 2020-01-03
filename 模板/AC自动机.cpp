#include <bits/stdc++.h>
#define N 10005
#define SIGSIZE 26
using namespace std;

struct Trie {
	int ch[SIGSIZE];
	int last;
	bool fin;
} tree[N];

int cnt=1;


void ins(string str)
{
	int p=0;
	for(unsigned int i=0;i<str.length();i++) {
		int c=str[i]-'A';
		Trie &cur=tree[p];
		if(!cur.ch[c]) cur.ch[c]=cnt++;
		p=cur.ch[c];
	}
	tree[p].fin=true;
}

void build()
{
	queue<int> q;
	static int f[N];
	for(int i=0;i<SIGSIZE;i++) {
		if(tree[0].ch[i]) {
			//f[tree[0].ch[i]]=0;
			q.push(tree[0].ch[i]);
		}/* else {
			tree[0].ch[i]=0;
		}*/
	}
	while(!q.empty()) {
		int u=q.front();q.pop();
		int fail=f[u];
		for(int i=0;i<SIGSIZE;i++) {
			int &v=tree[u].ch[i];
			if(!v) { //失配
				v=tree[fail].ch[i];
			} else { //可以匹配，更新v的最长公共前后缀(f[v])
				f[v]=tree[fail].ch[i];
				tree[v].last=tree[f[v]].fin?f[v]:tree[f[v]].last;
				q.push(v);
			}
		}
	}
}

bool find(string str)
{
	bool match=false;
	for(unsigned int i=0,p=0;i<str.length();i++) {
		p=tree[p].ch[str[i]-'A'];
		match=match||tree[p].fin;
		for(int l=(tree[p].fin)?p:(tree[p].last);l;l=tree[l].last) { //非结束节点也要从last开始匹配，可能有
			cout<<i+1<<":"<<l<<endl;								//某个串是当前串的后缀
		}
	}
	return match;
}

int main()
{
	int m,n;
	string str;
	cin>>n>>m;
	while(n--) {
		cin>>str;
		ins(str);
	}
	build();
	while(m--) {
		cin>>str;
		cout<<find(str)<<endl;
	}
	return 0;
}