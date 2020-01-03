#include <iostream>
#include <algorithm>
#include <map>
#define N 90
#define P 1000000000LL
using namespace std;

long long mat[N][N];
char dat[N][N];
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
map<pair<int,int>,int> id;
int tot;

int f(int x,int y)
{
	if(!id.count(make_pair(x,y)))
		return id[make_pair(x,y)]=tot++;
	else
		return id[make_pair(x,y)];
}

long long det(long long mat[N][N],int l)
{
	long long ans=1;

	for(int i=0;i<l;i++) {
		int repr=-1;
		for(int j=i;j<l;j++) {
			if(mat[i][j]) {
				repr=j;
				break;
			}
		}

		if(repr<0) return 0;

		for(int j=repr+1;j<l;j++) {
			int a=repr,b=j;
			while(mat[i][b]) {
				long long d=mat[i][a]/mat[i][b];
				for(int k=0;k<l;k++) {
					mat[k][a]=(mat[k][a]-(d*mat[k][b])%P+P)%P;
				}
				swap(a,b);
			}
			repr=a;
		}

		if(repr!=i) {
			for(int j=0;j<l;j++)
				swap(mat[j][repr],mat[j][i]);
			ans*=-1;
		}

		ans=(ans*mat[i][i]+P*P)%P;
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		cin>>dat[i];
	}

	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(dat[i][j]=='*')
				continue;

			int deg=0,cur=f(i,j);
			for(int k=0;k<4;k++) {
				int ni=i+dx[k],nj=j+dy[k];
				if(ni<0||nj<0||ni>=n||nj>=m||dat[ni][nj]=='*')
					continue;
				deg++;
				mat[f(ni,nj)][cur]=-1;
			}

			mat[cur][cur]=deg;
		}
	}

	cout<<det(mat,tot-1)<<endl;
	return 0;
}