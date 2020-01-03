//地鼠游戏 时间倒流+贪心+堆
#include <iostream>
#include <algorithm>
#include <queue>
#define N 105
using namespace std;

struct Mouse {
	int t,v;
	bool operator <(const Mouse &rhs) const {
		return t>rhs.t;
	}
} mouse[N];

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;

	for(int i=0;i<n;i++)
		cin>>mouse[i].t;
	for(int i=0;i<n;i++)
		cin>>mouse[i].v;

	sort(mouse,mouse+n);

	priority_queue<int> pq;
	int ans=0;
	for(int t=n,i=0;t;t--) {
		while(mouse[i].t>=t) pq.push(mouse[i++].v);
		if(!pq.empty()) {
			ans+=pq.top();
			pq.pop();
		}
	}

	cout<<ans<<endl;
	return 0;
}