//POI2001 病毒 AC自动机+判圈
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define N 35005
using namespace std;

struct Trie {
	int ch[2];
} trie[N];
int cnt=1;
int vis[N];
char buf[N];

void ins(char *str)
{
	int cur=0;
	for(;*str!='\0';str++) {
		int &pch=trie[cur].ch[*str-'0'];
		if(!pch) pch=cnt++;
		cur=pch;
	}
	vis[cur]=-1;
}

void getfail()
{
	static int fail[N];
	//memset(0)
	queue<int> q;
	if(trie[0].ch[0]) q.push(trie[0].ch[0]);
	if(trie[0].ch[1]) q.push(trie[0].ch[1]);
	//fail[0]=fail[trie[0].ch[i]]=0
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<2;i++) {
			int &v=trie[u].ch[i];
			if(v) {
				fail[v]=trie[fail[u]].ch[i];
				if(vis[fail[v]]<0) vis[v]=-1;
				q.push(v);
			} else {
				v=trie[fail[u]].ch[i];
			}
		}
	}
}

bool dfs(int u)
{
	vis[u]=1;
	for(int i=0;i<2;i++) {
		int v=trie[u].ch[i];
		if(vis[v]>0||(vis[v]==0&&dfs(v))) return true;
	}
	vis[u]=-1;
	return false;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>buf;
		ins(buf);
	}
	getfail();
	if(dfs(0)) cout<<"TAK"<<endl;
	else cout<<"NIE"<<endl;
	return 0;
}