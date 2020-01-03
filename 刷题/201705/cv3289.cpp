#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n,ans=1,last,prev,x;
	cin>>n>>last;
	prev=last;
	for(int i=1;i<n;i++) {
		cin>>x;
		if((long long)(last-prev)*(prev-x)>=0) { //注意两数相乘会导致int溢出……
			prev=x;
			continue;
		}
		last=prev;
		prev=x;
		ans++;
	}
	if(x!=last) ans++;
	cout<<ans<<endl;
	return 0;
}