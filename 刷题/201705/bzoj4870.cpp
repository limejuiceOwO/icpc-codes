#include <iostream>
#include <algorithm>
#include <cstring>
#define N 55
using namespace std;

long long mat[N][N],ans[N][N],tmp[N][N];
long long n,p,K,r;

void mmul(long long A[N][N],long long B[N][N],long long X[N][N])
{
	memset(X,0,sizeof(mat));
	for(int i=0;i<K;i++) {
		for(int j=0;j<K;j++) {
			for(int k=0;k<K;k++) {
				X[i][j]=(X[i][j]+A[i][k]*B[k][j])%p;
			}
		}
	}
}

int main()
{
	cin>>n>>p>>K>>r;
	long long z=n*K;
	for(int i=0;i<K;i++) {
		mat[i][i]++;
		mat[i][(i-1+K)%K]++;
		ans[i][i]=1;
	}
	while(z) {
		if(z&1) {
			memcpy(tmp,ans,sizeof(mat));//别偷懒……
			mmul(tmp,mat,ans);
		}
		mmul(mat,mat,tmp);
		memcpy(mat,tmp,sizeof(mat));
		z>>=1;	
	}
	cout<<ans[r][0]<<endl;
	return 0;
}