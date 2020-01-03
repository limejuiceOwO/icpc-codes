#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	long long n,t;
	cin>>n>>t;
	long long m=pow(10,t);
	n%=m;
	long long x=(n*n)%m;
	for(int i=1;i<=m;i++) {
		if(x==n) {
			cout<<i<<endl;
			return 0;
		}
		x=(x*n)%m;
	}
	cout<<"-1"<<endl;
	return 0;
}