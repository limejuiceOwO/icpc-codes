#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 105
#define P 2009
using namespace std;

int mat[N][N],ans[N][N];
char buf[N];

void mul(int a[N][N],int b[N][N],int s)
{
	static int t[N][N];
	memset(t,0,sizeof(t));
	for(int i=0;i<s;i++) {
		for(int j=0;j<s;j++) {
			for(int k=0;k<s;k++) {
				t[i][j]+=a[i][k]*b[k][j];
				t[i][j]%=P;
			}
		}
	}
	memcpy(a,t,sizeof(t));
}

int p(int a,int b)
{
	return a*9+b;
}

int main()
{
	int n,t;
	scanf("%d%d",&n,&t);
	for(int i=0;i<n;i++) {
		scanf("%s",buf);
		for(int j=0;j<8;j++) {
			mat[p(i,j)][p(i,j+1)]=1;
		}
		for(int j=0;j<n;j++) {
			int d=buf[j]-'0';
			if(d) mat[p(i,d-1)][p(j,0)]=1;
		}
	}

	for(int i=0;i<9*n;i++)
		ans[i][i]=1;
	while(t) {
		if(t&1) mul(ans,mat,9*n);
		mul(mat,mat,9*n);
		t>>=1;
	}
	
	printf("%d\n",ans[p(0,0)][p(n-1,0)]);
	return 0;
}