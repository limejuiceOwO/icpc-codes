#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

struct Floor {
	int a,b;
	bool operator <(const Floor &rhs) const {
		return a+b<rhs.a+rhs.b;
	}
} flr[N];

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		int n;
		cin>>n;
		if(cin.eof()) break;
		for(int i=0;i<n;i++)
			cin>>flr[i].a>>flr[i].b;

		sort(flr,flr+n);

		long long ans=0,sum=0;
		for(int i=0;i<n;i++) {
			ans=max(ans,sum-flr[i].b);
			sum+=flr[i].a;
		}

		cout<<ans<<endl;
	}

	return 0;
}