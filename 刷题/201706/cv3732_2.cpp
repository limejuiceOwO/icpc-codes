#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
//#include <iostream>
#define N 105
#define B 10005
#define PCNT 5
#define MAXP 30005
using namespace std;

const int p[PCNT]={10007,10487,20173,23333,27337};
int arr[N][PCNT],ans[N]; //arr[i][j]:-第i个系数模p[j]的值
char vis[PCNT][MAXP]; //vis[i][j]:-j模p[i]为0

void get(int i)
{
	static char stk[B];
	int top=0,sgn=1;

	if((stk[top]=getchar())=='-')
		sgn=-1;
	else
		top++;

	while(isdigit(stk[top]=getchar()))
		top++;

	int power[PCNT]={1,1,1,1,1};
	while(top--) {
		for(int j=0;j<PCNT;j++) {
			arr[i][j]=(1LL*power[j]*(stk[top]-'0')+arr[i][j])%p[j];
			power[j]=(10LL*power[j])%p[j];
		}
	}

	for(int j=0;j<PCNT;j++)
		arr[i][j]*=sgn;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	getchar();

	for(int i=0;i<=n;i++)
		get(i);

	for(int x=1;x<p[PCNT-1];x++) {
		int ans2[PCNT];

		for(int j=0;j<PCNT;j++)
			ans2[j]=arr[n][j];

		for(int i=n-1;i>=0;i--)
			for(int j=0;j<PCNT;j++)
				ans2[j]=(1LL*ans2[j]*x+arr[i][j])%p[j];

		for(int j=0;j<PCNT;j++)
			if(ans2[j]==0) vis[j][x]=1;
	}

	int cnt=0;
	for(int x=1;x<=m;x++) {
		bool ok=true;
		for(int j=0;j<PCNT;j++)
			if(!vis[j][x%p[j]]) ok=false;

		if(ok) ans[cnt++]=x;
	}
	printf("%d\n",cnt);

	for(int i=0;i<cnt;i++)
		printf("%d\n",ans[i]);

	return 0;
}