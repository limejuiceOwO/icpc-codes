#include <cstdio>
#include <algorithm>
#define N 1005
using namespace std;

int arr[N][N];
int ans1[N][N],ans2[N][N];
int q1[N],q2[N],pos1[N],pos2[N];

int main()
{
	int a,b,n;
	scanf("%d%d%d",&a,&b,&n);

	for(int i=0;i<a;i++) {
		for(int j=0;j<b;j++) {
			scanf("%d",&arr[i][j]);
		}
	}

	int h1,t1,h2,t2;
	for(int i=0;i<a;i++) {
		h1=t1=h2=t2=0;
		for(int j=0;j<n-1;j++) {
			while(h1<t1&&q1[t1-1]<=arr[i][j]) t1--; //max
			pos1[t1]=j;
			q1[t1++]=arr[i][j];
			while(h2<t2&&q2[t2-1]>=arr[i][j]) t2--; //min
			pos2[t2]=j;
			q2[t2++]=arr[i][j];
		}
		for(int j=-1;j<b-n;j++) {
			while(h1<t1&&q1[t1-1]<=arr[i][j+n]) t1--;
			pos1[t1]=j+n;
			q1[t1++]=arr[i][j+n];
			while(h2<t2&&q2[t2-1]>=arr[i][j+n]) t2--;
			pos2[t2]=j+n;
			q2[t2++]=arr[i][j+n];
			ans1[i][j+1]=q1[h1];
			ans2[i][j+1]=q2[h2];
			if(pos1[h1]<=j+1) h1++;
			if(pos2[h2]<=j+1) h2++;
		}
	}

	int ans=1000000005;
	for(int j=0;j<=b-n;j++) {
		h1=t1=h2=t2=0;
		for(int i=0;i<n-1;i++) {
			while(h1<t1&&q1[t1-1]<=ans1[i][j]) t1--;
			pos1[t1]=i;
			q1[t1++]=ans1[i][j];
			while(h2<t2&&q2[t2-1]>=ans2[i][j]) t2--;
			pos2[t2]=i;
			q2[t2++]=ans2[i][j];
		}
		for(int i=-1;i<a-n;i++) {
			while(h1<t1&&q1[t1-1]<=ans1[i+n][j]) t1--;
			pos1[t1]=i+n;
			q1[t1++]=ans1[i+n][j];
			while(h2<t2&&q2[t2-1]>=ans2[i+n][j]) t2--;
			pos2[t2]=i+n;
			q2[t2++]=ans2[i+n][j];
			ans=min(ans,q1[h1]-q2[h2]);
			if(pos1[h1]<=i+1) h1++;
			if(pos2[h2]<=i+1) h2++;
		}
	}

	printf("%d\n",ans);
	return 0;
}