#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int maxn[10001];
int maxnp[10001];

bool cmp (const int a,const int b) //下降 
{
	return a>b;
}

int main()
{
	int n,d=0;
	cin>>n;
	for(int i=0;i<n;i++) {
		int num;
		cin>>num;
		//int j=upper_bound(maxn,maxn+d,num)-maxn; //不下降 
		int j=lower_bound(maxn,maxn+d,num)-maxn; //下降 
		if(j==d) d++;
		maxnp[j]=j==0?0:maxn[j-1];
		maxn[j]=num;
	}
	maxnp[d]=maxn[d-1];
	cout<<d<<endl;
	for(int i=1;i<=d;i++) cout<<maxnp[i]<<' ';
	return 0;
}
