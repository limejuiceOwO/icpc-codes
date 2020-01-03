//HNOI2011 XOR和路径 概率dp+高斯消元
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 105
using namespace std;
vector<int> G[N],w[N];
double mat[N][N],res[N];

double solve(int n,int s)
{
	memset(mat,0,sizeof(mat));
	memset(res,0,sizeof(res));
	mat[n][n]=1;
	for(int u=1;u<n;u++) {
		mat[u][u]=1;
		double sz=G[u].size();
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=G[u][i],ww=w[u][i]&(1<<s);
			if(ww) {
				res[u]+=1.0/sz;
				mat[u][v]+=1.0/sz;
			} else {
				mat[u][v]-=1.0/sz;
			}
		}
	}

	static int repr[N];
	memset(repr,0,sizeof(repr));
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(mat[i][j]) {
				repr[i]=j;
				break;
			}
		}

		double d=mat[i][repr[i]];
		for(int j=1;j<=n;j++) {
			mat[i][j]/=d;
		}
		res[i]/=d;
		for(int j=1;j<=n;j++) {
			if(i==j) continue;
			double d2=mat[j][repr[i]];
			for(int k=1;k<=n;k++) {
				mat[j][k]-=mat[i][k]*d2;
			}
			res[j]-=res[i]*d2;
		}
	}
	
	for(int i=1;i<=n;i++) {
		if(repr[i]==1) {
			return res[i];
		}
	}

	return -1;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0,u,v,ww;i<m;i++) {
		scanf("%d%d%d",&u,&v,&ww);
		G[u].push_back(v);
		w[u].push_back(ww);
		if(u!=v) { //注意是无向边
			G[v].push_back(u);
			w[v].push_back(ww);
		}
	}

	double ans=0;
	for(int s=0;s<30;s++) {
		ans+=solve(n,s)*(1<<s);
	}
	printf("%.3lf",ans);
	return 0;
}