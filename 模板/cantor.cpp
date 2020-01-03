#include <iostream>
#include <algorithm>
#define N 15
using namespace std;

int pow[N],arr[N];

int cantor(int n,const int arr[]) //O(n^2)
{
	int ans=0;
	char vis[N];

	for(int i=0;i<=n;i++)
		vis[i]=0;

	for(int i=0;i<n-1;i++) {
		vis[arr[i]]=1;

		int cnt=0;
		for(int j=1;j<arr[i];j++)
			cnt+=vis[j];

		ans+=(arr[i]-cnt-1)*pow[n-i-1];
	}

	return ans;
}

void rev_cantor(int v,int n,int arr[]) //O(n^2)
{
	char vis[N];

	for(int i=0;i<=n;i++) {
		vis[i]=0;
	}

	for(int i=0;i<n-1;i++) {
		int j=1;
		for(int p=v/pow[n-i-1]+1;j<=n&&p;p-=!vis[j++]);

		vis[arr[i]=(j-1)]=1;
		v%=pow[n-i-1];
	}

	int j;
	for(j=1;j<=n&&vis[j];j++);
	arr[n-1]=j;
}

int main()
{
	int n,v;
	cin>>n>>v;
//	cin>>n;
//	for(int i=0;i<n;i++) {
//		cin>>arr[i];
//	}

	pow[1]=1;
	for(int i=2;i<=n;i++) {
		pow[i]=pow[i-1]*i;
	}

	rev_cantor(v,n,arr);
//	cout<<cantor(n,arr)<<endl;
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<endl;

	return 0;
}