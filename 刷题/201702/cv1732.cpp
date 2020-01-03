#include <bits/stdc++.h>
#define M 1000000007
using namespace std;

void mul(int mat1[2][2],int mat2[2][2])
{
	int ans[2][2];
	memset(ans,0,sizeof(ans));
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			for(int k=0;k<2;k++) {
				ans[i][j]=((long long)ans[i][j]+(long long)mat1[i][k]*mat2[k][j])%M;
			}
		}
	}
	memcpy(mat1,ans,sizeof(ans));
}

int main()
{
	while(1) {
		long long n;
		int ans[2][2]={{1,0},{0,1}},mat[2][2]={{1,1},{1,0}};
		cin>>n;
		if(cin.eof()) break;
		while(n) {
			if(n&1) mul(ans,mat);
			mul(mat,mat);
			n>>=1;
		}
		cout<<ans[0][1]%M<<endl;
	}
	return 0;
}