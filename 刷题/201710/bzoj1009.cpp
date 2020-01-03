//HNOI2008 GT考试 KMP+矩阵乘法优化dp
#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 25
using namespace std;

int n,m,k;
char str[N];
int unluck[N],nxt[N];
int mat[N][N],res[N][N];

void mul(int a[N][N],int b[N][N])
{
	static int tmp[N][N];
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<m;i++) {
		for(int j=0;j<m;j++) {
			for(int kk=0;kk<m;kk++) {
				tmp[i][j]=(tmp[i][j]+a[i][kk]*b[kk][j])%k;
			}
		}
	}
	memcpy(a,tmp,sizeof(tmp));
}

void qpow(int nn)
{
	while(nn) {
		if(nn&1) mul(res,mat);
		mul(mat,mat);
		nn>>=1;
	}
}

int main()
{
	scanf("%d%d%d%s",&n,&m,&k,str);

	for(int i=0;i<m;i++) {
		unluck[i]=str[i]-'0';
	}

	nxt[0]=nxt[1]=0;
	for(int i=1,j;i<m;i++) {
		j=nxt[i];
		while(j&&unluck[j]!=unluck[i])
			j=nxt[j];
		nxt[i+1]=(unluck[j]==unluck[i] ? j+1 : 0);
	}

	for(int i=0;i<m;i++) {
		for(int p=0;p<10;p++) {
			if(unluck[i]==p) {
				if(i==m-1) continue;
				mat[i][i+1]++; //每个元素的贡献在列上统计，所以要在列上加
			} else {
				int j=nxt[i];
				while(j&&unluck[j]!=p)
					j=nxt[j];
				mat[i][(unluck[j]==p ? j+1 : 0)]++;
			}
		}
	}

	for(int i=0;i<m;i++) {
		res[i][i]=1;
	}
	qpow(n);

	int ans=0;
	for(int i=0;i<m;i++) {
		ans=(ans+res[0][i])%k;
	}
	printf("%d\n",ans);
	return 0;
}