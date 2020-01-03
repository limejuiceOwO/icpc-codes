#include <iostream>
#include <algorithm>
#define N 70
using namespace std;

int ans[N];

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		long long n;
		int k;
		cin>>n>>k;
		if(cin.eof()) break;

		if(n==0) {
			cout<<"0"<<endl;
			continue;
		}

		if(n<0&&k>0) {
			n=-n;
			cout<<"-";
		}

		int cnt=0;
		while(n) {
			if(n>0) {
				ans[cnt++]=n%abs(k);
				n/=k;
			} else {
				ans[cnt++]=(n%abs(k)+abs(k))%abs(k);
				n=(n/k)+(n%abs(k)!=0);
			}
		}

		for(int i=cnt-1;i>=0;i--) {
			cout<<ans[i];
		}
		cout<<endl;
	}
	return 0;
}