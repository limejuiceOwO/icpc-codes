#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
//#include <iostream>
#define N 105
#define B 10005
#define P1 37554271
#define P2 46512377
using namespace std;

int arr1[N],arr2[N],ans[N];
int cnt=0;

void get(int i)
{
	static char stk[B];
	int top=0,sgn=1;

	scanf("%s",stk);
	top=strlen(stk);

	if(stk[0]=='-') {
		stk[0]='0';
		sgn=-1;
	}

	int power1=1,power2=1;
	while(top--) {
		arr1[i]=(1LL*power1*(stk[top]-'0')+arr1[i])%P1;
		arr2[i]=(1LL*power2*(stk[top]-'0')+arr2[i])%P2;
		power1=(10LL*power1)%P1;
		power2=(10LL*power2)%P2;
	}

	arr1[i]*=sgn;
	arr2[i]*=sgn;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	getchar();

	for(int i=0;i<=n;i++)
		get(i);
	//for(int i=0;i<=n;i++) cout<<arr1[i]<<" "<<arr2[i]<<endl;

	for(int x=1;x<=m;x++) {
		int ans1=arr1[n],ans2=arr2[n];

		for(int i=n-1;i>=0;i--) {
			ans1=(1LL*ans1*x+arr1[i])%P1;
			ans2=(1LL*ans2*x+arr2[i])%P2;
		}

		if(ans1==0&&ans2==0) ans[cnt++]=x;
	}

	printf("%d\n",cnt);
	for(int i=0;i<cnt;i++) 
		printf("%d\n",ans[i]);

	return 0;
}