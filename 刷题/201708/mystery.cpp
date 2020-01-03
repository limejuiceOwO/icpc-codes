#include <iostream>
#include <algorithm>
#include <cmath>
#define N 11
using namespace std;

long long dp[N][10*N][10*N][10*N];//长度为i，数位和为j，总和模k余l

long long calc(int x)
{
	if(x<=10)
		return x;

	static int arr[N];
	long long ans=0;
	int len;
	for(len=0;x;len++,x/=10) {
		arr[len]=x%10;
	}
	
	int sum=0,bsum=0,p=pow(10,len-1);
	for(int i=len-1;i>=0;i--,p/=10) {
		for(int m=0;m<arr[i];m++) {
			for(int j=(bsum+m==0 ? 1 : 0);j<=9*i;j++) {
				int k=bsum+m+j;
				ans+=dp[i][j][k][(k-(sum+m*p)%k)%k];
			}
		}
		bsum+=arr[i];
		sum+=arr[i]*p;
		// cout<<sum<<" "<<bsum<<endl;
	}

	bsum-=arr[0];
	sum-=arr[0];
	for(int i=0;i<=arr[0];i++) {
		if((sum+i)%(bsum+i)==0)
			ans++;
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	for(int j=0;j<10;j++) {
		for(int k=1;k<=9*N;k++) {
			dp[1][j][k][j%k]=1;
		}
	}

	int p=10;
	for(int i=2;i<N;i++,p*=10) {
		for(int j=0;j<=9*N;j++) {
			for(int k=1;k<=9*N;k++) {
				for(int l=0;l<k;l++) {
					for(int m=0;m<min(10,j+1);m++) { 
						dp[i][j][k][l]+=dp[i-1][j-m][k][((l-p*m)%k+k)%k];
					}
				}
			}
		}
	}

	while(1) {
		int l,r;
		cin>>l>>r;
		if(cin.eof()) break;
		cout<<calc(r)-calc(l-1)<<endl;
	}
	return 0;
}