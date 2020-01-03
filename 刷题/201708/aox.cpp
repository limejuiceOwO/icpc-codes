#include <iostream>
#include <algorithm>
#include <cstring>
#define N 128
using namespace std;

long long arr[N],src[N];

void fwt(long long arr[],int n,int type)
{
	if(n==1) return;
	int m=n>>1;
	fwt(arr,m,type);
	fwt(arr+m,m,type);
	for(int i=0;i<m;i++) {
		long long a,b;
		switch(type) {
			case 2:
			a=arr[i],b=arr[i+m];
			arr[i]=a+b;
			arr[i+m]=a-b;
			break;
			case 1:
			arr[i]+=arr[i+m];
			break;
			case 3:
			arr[i+m]+=arr[i];
			break;
		}
	}
}

void dfwt(long long arr[],int n,int type)
{
	if(n==1) return;
	int m=n>>1;
	dfwt(arr,m,type);
	dfwt(arr+m,m,type);
	for(int i=0;i<m;i++) {
		long long a,b;
		switch(type) {
			case 2:
			a=arr[i],b=arr[i+m];
			arr[i]=(a+b)>>1;
			arr[i+m]=(a-b)>>1;
			break;
			case 1:
			arr[i]-=arr[i+m];
			break;
			case 3:
			arr[i+m]-=arr[i];
			break;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	int t;
	cin>>t;

	while(t--) {
	int n,c,mx=0;
		cin>>n>>c;
		memset(arr,0,sizeof(arr));
		for(int i=0;i<n;i++) {
			int x;
			cin>>x;
			mx=max(mx,x);
			arr[x]=1;
		}

		int nn=1;
		while(nn<mx) nn<<=1;
		n=nn;

		memcpy(src,arr,sizeof(src));
		fwt(arr,n,c);
		for(int j=0;j<n;j++) {
			arr[j]*=arr[j];
		}
		dfwt(arr,n,c);

		for(int i=n-1;i>=0;i--) {
			if(arr[i]-src[i]*(c!=2)) {
				cout<<i<<endl;
				break;
			}
		}
	}

	return 0;
}