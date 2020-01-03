#include <cstdio>
#include <iostream>
#include <algorithm>
#define N 45
using namespace std;

unsigned long long mat[N],msk[N][N];
char ans[N][N],res[N];

void gauss(int n)
{
	for(int j=0;j<n;j++) {
		int i;
		for(i=j;i<n;i++) {
			if(mat[i]&(1ULL<<j)) {
				swap(mat[i],mat[j]);
				break;
			}
		}
		if(i==n) continue; //如果第i行存在主元会发生什么???
		for(i=j+1;i<n;i++) {
			if(mat[i]&(1ULL<<j)) {
				mat[i]^=mat[j];
			}
		}
	}

	for(int i=n-1;i>=0;i--) {
		ans[0][i]=mat[i]&(1ULL<<i) ? ans[0][i] : 1;
		if(ans[0][i]) {
			for(int j=i-1;j>=0;j--) {
				if(mat[j]&(1ULL<<i))
					ans[0][j]^=1;
			}
		}
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);

	for(int j=0;j<m;j++) {
		msk[0][j]=(1ULL<<j);
	}

	for(int i=1;i<n;i++) {
		for(int j=0;j<m;j++) {
			msk[i][j]=msk[i-1][j];
			if(j>0) msk[i][j]^=msk[i-1][j-1];
			if(j<m-1) msk[i][j]^=msk[i-1][j+1];
			if(i>1) msk[i][j]^=msk[i-2][j];
		}
	}

	for(int j=0;j<m;j++) {
		mat[j]=msk[n-1][j];
		if(j>0) mat[j]^=msk[n-1][j-1];
		if(j<m-1) mat[j]^=msk[n-1][j+1];
		if(n>1) mat[j]^=msk[n-2][j];
	}
	/*
	for(int i=0;i<m;i++) {
		for(int j=0;j<m;j++)
			cout<<(bool)(mat[i]&(1ULL<<j));
		cout<<endl;
	}
	*/
	gauss(m);
	/*
	for(int i=0;i<m;i++) {
		for(int j=0;j<m;j++)
			cout<<(bool)(mat[i]&(1ULL<<j));
		cout<<endl;
	}	
	*/
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			printf("%d ",(int)ans[i][j]);
		}
		puts("");

		for(int j=0;j<m;j++) {
			ans[i+1][j]=ans[i][j];
			if(j>0) ans[i+1][j]^=ans[i][j-1];
			if(j<m-1) ans[i+1][j]^=ans[i][j+1];
			if(i>0) ans[i+1][j]^=ans[i-1][j];
		}
	}

	return 0;
}