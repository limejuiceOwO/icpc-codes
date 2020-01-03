#include <iostream>
#include <algorithm>
#include <cstring>
#define N 70
using namespace std;

int arr[N];
char vis[N];
int sum,n;

bool dfs(int l,int c=0,int d=0)
{
	if(l*d==sum) return true;

	for(int i=0;i<n;i++) {
		if(vis[i]) continue;
		vis[i]=1;
		if(l-c>arr[i]&&dfs(l,c+arr[i],d))
			return true;
		if(l-c==arr[i]&&dfs(l,0,d+1))
			return true;
		vis[i]=0;
		if(c==0) return false;
		while(i+1<n&&arr[i]==arr[i+1]) i++;
	}

	return false;
}

int main()
{
	while(1) {
		int mx=0;
		sum=0;
		cin>>n;
		if(!n) break;
		for(int i=0;i<n;i++) {
			cin>>arr[i];
			sum+=arr[i];
			mx=max(mx,arr[i]);
		}

		sort(arr,arr+n,greater<int>());
		memset(vis,0,sizeof(vis));

		for(int i=mx;i<sum;i++) {
			if(sum%i==0&&dfs(i)) {
				cout<<i<<endl;
				goto end;
			}
		}
		cout<<sum<<endl;
		end:while(0);
	}

	return 0;
}