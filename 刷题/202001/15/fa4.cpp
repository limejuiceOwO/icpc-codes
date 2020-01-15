//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#define N 10005
using namespace std;

int l[N],r[N];

int main()
{
	//ios::sync_with_stdio(false);
	int t; scanf("%d",&t);
	while(t--) {
		int n; scanf("%d",&n);
		set<int> bare;
		for(int i = 0;i < n;i++) {
			scanf("%d",&l[i]);
			scanf("%d",&r[i]);
			bare.insert(l[i]);
			bare.insert(r[i]);
		}
		int ans = 0;
		for(int i = n - 1;i >= 0;i--) {
			set<int>::iterator iter = bare.lower_bound(l[i]);
			if(iter != bare.end() && *iter <= r[i]) {
				ans++;
				while(iter != bare.end() && *iter <= r[i]) {
					bare.erase(*(iter++));
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}