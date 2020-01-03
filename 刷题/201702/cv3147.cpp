//矩阵乘法 2
#include <iostream>
#include <algorithm>
#define N 805
using namespace std;

int mat1[N][N],mat2[N][N];

int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>mat1[i][j];
			if(i>0) mat1[i][j]+=mat1[i-1][j];
		}
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>mat2[i][j];
			if(j>0) mat2[i][j]+=mat2[i][j-1];
		}
	}
	while(m--) {
		int x1,y1,x2,y2;
		long long ans=0;
		cin>>x1>>y1>>x2>>y2;
		x1--;x2--;y1--;y2--;
		if(x1>x2) swap(x1,x2);
		if(y1>y2) swap(y1,y2);
		for(int k=0;k<n;k++) {
			ans+=(long long)(mat1[x2][k]-((x1>0)?mat1[x1-1][k]:0))*(mat2[k][y2]-((y1>0)?mat2[k][y1-1]:0));
		}
		cout<<ans<<endl;
	}
	return 0;
}