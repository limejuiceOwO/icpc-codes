#include<bits/stdc++.h>
#define SIGSIZE 26
#define N 1000
using namespace std;

struct Node {
	int ch[SIGSIZE];
	bool last;
} nodes[N];
int nodesize=1;

void ins(string str) {
	int p=0;
	for(int i=0;i<str.length();i++) {
		int &ch=nodes[p].ch[str[i]-'a'];
		if(!ch) ch=nodesize++;
		p=ch;
	}
	nodes[p].last=true;
}

bool find(string str) {
	int p=0;
	for(int i=0;i<str.length();i++) {
		int &ch=nodes[p].ch[str[i]-'a'];
		if(!ch) return false;
		p=ch;
	}
	return nodes[p].last;
}

void listall(int p,int d) {
	static char buf[N];
	if(nodes[p].last) cout<<buf<<endl;
	for(int i=0;i<SIGSIZE;i++) {
		if(nodes[p].ch[i]) {
			buf[d]='a'+i;
			listall(nodes[p].ch[i],d+1);
			buf[d]='\0';
		}
	}
}

int main()
{
	string str;
	while(1) {
		int cmd;
		cin>>cmd>>str;
		if(cmd==0) ins(str);
		else if(cmd==1) cout<<find(str)<<endl;
		else listall(0,0);
	}
	return 0;
}
