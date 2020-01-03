#include <bits/stdc++.h>
using namespace std;

void mul(double mat1[2][2],double mat2[2][2])
{
	double ans[2][2];
	memset(ans,0,sizeof(ans));
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			for(int k=0;k<2;k++) {
				ans[i][j]+=mat1[i][k]*mat2[k][j];
			}
		}
	}
	memcpy(mat1,ans,sizeof(ans));
}

int main()
{
	long long n,f0,f1;
	double mat[2][2],ans[2][2];
	cin>>f0>>f1>>mat[0][0]>>mat[0][1]>>n;
	mat[1][0]=1;mat[1][1]=0;
	ans[0][0]=ans[1][1]=1;
	ans[1][0]=ans[0][1]=0;
	n--;
	while(n) {
		if(n&1) mul(ans,mat);
		mul(mat,mat);
		n>>=1;
	}
	cout<<(long long)(((f1==0)?0:f1*ans[0][0])+((f0==0)?0:f0*ans[0][1]))<<endl;
	return 0;
}