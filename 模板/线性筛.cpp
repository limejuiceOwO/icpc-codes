#include<bits/stdc++.h>
#define N 10005
using namespace std;
bool prime[N];

void sieve(int n)
{
	vector<int> primelist;
	fill(prime,prime+n,true);
	prime[1]=false;
	for(int i=2;i<n;i++) {
		if(prime[i]) primelist.push_back(i);
		for(vector<int>::iterator v=primelist.begin();v!=primelist.end();v++) {
			if(i/(*v)==0||i*(*v)>n) break;
			prime[i*(*v)]=false;
		}
	}
}

int main()
{
	int n;
	cin>>n;
	sieve(n);
	for(int i=1;i<n;i++) {
		if(prime[i]) cout<<i<<endl;
	}
	return 0;
}