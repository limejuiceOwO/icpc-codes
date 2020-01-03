#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);

	int n,x,y,h,e;
	cin>>n>>x>>y>>h>>e;

	int cnt=0,mxcnt=0;
	priority_queue<int> pq;
	for(int i=0;i<n;i++) {
		int di;
		cin>>di;
		mxcnt=max(mxcnt,++cnt);
		pq.push(max(y,di));
		if(cnt*x>=e) {
			cout<<"YES"<<endl;
			cout<<i+1<<endl;
			return 0;
		}

		h-=di;
		while(h<=0) {
			if(pq.empty())
				goto end;
			h+=pq.top();
			pq.pop();
			cnt--;
		}
	}

	end:
	cout<<"NO"<<endl;
	cout<<mxcnt*x<<endl;
	return 0;
}