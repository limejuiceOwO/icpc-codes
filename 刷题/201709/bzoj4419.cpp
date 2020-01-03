//SHOI2013 发微博 暴力+打标记
#include <cstdio>
#include <algorithm>
#include <set>
#define N 200005
using namespace std;

set<int> tomo[N];
int ans[N],give[N];

int main()
{
	int n,m;
	char cmd[5];
	scanf("%d%d",&n,&m);

	for(int i=0,a,b;i<m;i++) {
		scanf("%s",cmd);
		if(cmd[0]=='!') {
			scanf("%d",&a);
			give[a]++;
		} else if(cmd[0]=='+') {
			scanf("%d%d",&a,&b);
			ans[a]-=give[b]; //去掉以前发过的
			ans[b]-=give[a];
			tomo[a].insert(b);
			tomo[b].insert(a);
		} else if(cmd[0]=='-') {
			scanf("%d%d",&a,&b);
			ans[a]+=give[b]; //加上以前发过的
			ans[b]+=give[a];
			tomo[a].erase(b);
			tomo[b].erase(a);
		}
	}

	for(int i=1;i<=n;i++) {
		for(set<int>::iterator it=tomo[i].begin();it!=tomo[i].end();it++) {
			ans[*it]+=give[i];
		}
	}

	for(int i=1;i<=n;i++) {
		printf("%d%s",ans[i],i<n ? " " : "");
	}
	return 0;
}