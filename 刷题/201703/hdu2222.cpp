#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define N 650005
#define M 1000005
using namespace std;

struct Trie {
	int ch[26];
	int cnt,last; 
} trie[N];
int cnt;
char buf[M];

void ins(char *str)
{
	int cur=0;
	for(;*str!='\0';str++) {
		int &pch=trie[cur].ch[*str-'a'];
		if(!pch) pch=cnt++;
		cur=pch;
	}
	trie[cur].cnt++;
}

void getfail()
{
	static int fail[N];
	memset(fail,0,sizeof(fail));
	queue<int> q;
	for(int i=0;i<26;i++) {
		if(trie[0].ch[i]) q.push(trie[0].ch[i]);
	}
	//fail[0]=fail[trie[0].ch[i]]=0
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<26;i++) {
			int &v=trie[u].ch[i];
			if(v) {
				fail[v]=trie[fail[u]].ch[i];
				trie[v].last=trie[fail[v]].cnt?fail[v]:trie[fail[v]].last;
				q.push(v);
			} else {
				v=trie[fail[u]].ch[i];
			}
		}
	}
}

int find(char *str)
{
	int len=strlen(str),p=0,ans=0;
	for(int i=0;i<len;i++) {
		p=trie[p].ch[str[i]-'a'];
		for(int l=p;l;l=trie[l].last) {
			ans+=trie[l].cnt;
			trie[l].cnt=0;
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	int t,n;
	cin>>t;
	while(t--) {
		cin>>n;
		memset(trie,0,sizeof(trie));
		cnt=1;
		for(int i=0;i<n;i++) {
			cin>>buf;
			ins(buf);
		}
		getfail();
		cin>>buf;
		cout<<find(buf)<<endl;
	}
	return 0;
}