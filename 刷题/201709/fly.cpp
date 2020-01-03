#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

int arr[N];
int ncnt;

int main()
{
	int n,x1,a,mod,x;
	cin>>n>>x1>>a>>mod;
	int i=0,st,ed;
	for(int i=0,x=x1;x<mod;i++) {
		x+=a;
	}
	st=i;
	x%=mod;
	for(;i<n;i++) {
		if(x>st&&x<st+a) arr[ncnt++]=x;
		x=x+a;
		if(x>a) x=ed=x%mod;
	}
	
	int seg=x%a;
	long long r=rev(arr);
	long long ans=r*s+((ncnt+1)*ncnt/2)*((seg-1)*seg/2);//+ncnt*ed*(ed-1)/2+st
	cout<<ans<<endl;
	return 0;
}