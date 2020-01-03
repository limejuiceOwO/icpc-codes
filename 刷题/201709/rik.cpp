#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long phi(long long n)
{
	long long bound=sqrt(n)+1;
	long long ans=n;
	for(int i=2;i<bound;i++) {
		if(n%i==0) {
			while(n%i==0) n/=i;
			ans=ans*(i-1)/i;
		}
	}
	if(n>1) ans=ans*(n-1)/n;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		long long n;
		cin>>n;
		if(cin.eof()) break;
		if(n>1)
			cout<<phi(n)*n/2<<endl;
		else
			cout<<"1"<<endl;
	}
	return 0;
}