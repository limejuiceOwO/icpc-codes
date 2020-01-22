#include <iostream>
#include <cstring>
#include <vector>
#define N 505
using namespace std;

char graph[N][N];
char vis[N];
int match[N];
int n,m;

vector<int> cat[2][N],dog[2][N];
typedef vector<int>::iterator Iter;

bool dfs(int u)
{
	vis[u] = 1;
	for(int v = 1;v <= m;v++) {
		if(graph[u][v] && (!match[v] || (!vis[match[v]] && dfs(match[v])))) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int bimatch()
{
	int res = 0;
	for(int u = 1;u <= n;u++) {
		memset(vis,0,sizeof(vis));
		if(dfs(u)) res++;
	}
	return res;
}

int parse(string s)
{
	int ans = 0;
	for(int i = 1;i < s.length();i++)
		ans = ans * 10 + s[i] - '0';
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	while(1) {
		int nn,mm,q; cin >> nn >> mm >> q;
		if(cin.eof())
			return 0;
		memset(match,0,sizeof(match));
		memset(graph,0,sizeof(graph));
		for(int i = 1;i <= nn;i++) {
			cat[0][i].clear();
			cat[1][i].clear();
		}
		for(int i = 1;i <= mm;i++) {
			dog[0][i].clear();
			dog[1][i].clear();
		}
		n = m = q;
		for(int i = 1;i <= q;i++) {
			string like,dislike;
			cin >> like >> dislike;
			if(like[0] == 'C') {
				cat[0][parse(like)].push_back(i);
				dog[1][parse(dislike)].push_back(i);
			} else if(like[0] == 'D') {
				dog[0][parse(like)].push_back(i);
				cat[1][parse(dislike)].push_back(i);
			} else {
				return 1;
			}
		}
		for(int i = 1;i <= nn;i++) {
			for(Iter it1 = cat[0][i].begin();it1 != cat[0][i].end();++it1) {
				for(Iter it2 = cat[1][i].begin();it2 != cat[1][i].end();++it2) {
					int u = *it1,v = *it2;
					graph[u][v] = 1;
				}
			}
		}
		for(int i = 1;i <= mm;i++) {
			for(Iter it1 = dog[0][i].begin();it1 != dog[0][i].end();++it1) {
				for(Iter it2 = dog[1][i].begin();it2 != dog[1][i].end();++it2) {
					int u = *it1,v = *it2;
					graph[v][u] = 1;
				}
			}
		}
		cout << q - bimatch() << endl;
	}
}