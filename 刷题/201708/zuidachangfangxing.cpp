#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

pair<int,int> st[N];

int main()
{
	int n,ans=0,top=0;
	cin>>n;
	for(int i=0;i<n;i++) {
		int x;
		cin>>x;
		int len=1;
		while(top&&st[top-1].first>=x) {
			len+=st[top-1].second;
			top--;
		}
		st[top++]=make_pair(x,len);
		ans=max(ans,x*len);
	}

	int l=0;
	while(top) {
		l+=st[top-1].second;
		ans=max(ans,st[top-1].first*l);
		top--;
	}

	cout<<ans<<endl;
	return 0;
}