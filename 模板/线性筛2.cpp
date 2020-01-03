#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

int mindiv[N],prime[N];

int linearsieve(int n)
{
	int cnt=0;

	mindiv[1]=1;
	for(int i=2;i<=n;i++) {
		if(!mindiv[i]) {
			mindiv[i]=i;
			prime[cnt++]=i;
		}
		for(int j=0;j<cnt&&prime[j]<=mindiv[i]&&i*prime[j]<=n;j++)
			mindiv[i*prime[j]]=prime[j];
	}

	return cnt;
}

int main()
{
	int n;
	cin>>n;
	int ans=linearsieve(n);
	for(int i=0;i<ans;i++)
		cout<<prime[i]<<" ";
	cout<<endl;
	return 0;
}