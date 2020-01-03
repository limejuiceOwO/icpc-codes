#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 50005
#define EPS 1e-7
#define INF 10000000
using namespace std;

struct Line {
	int id;
	double A,B;
	bool operator <(const Line &rhs) const
	{
		return fabs(A-rhs.A)<EPS ? B>rhs.B : A<rhs.A;
	}
} line[N];

double inter[N];
int stk[N],top;
int ans[N];

double intersectx(const Line &a,const Line &b)
{
	return (a.B-b.B)/(b.A-a.A);
}

int main()
{
	int n;
	scanf("%d",&n);

	for(int i=0;i<n;i++) {
		line[i].id=i+1;
		scanf("%lf%lf",&line[i].A,&line[i].B);
	}

	sort(line,line+n);

	stk[top++]=0;
	inter[0]=-INF;

	for(int i=1;i<n;i++) {
		if(fabs(line[i-1].A-line[i].A)<EPS) continue;
		while(top&&intersectx(line[stk[top-1]],line[i])-inter[top-1]<EPS) top--;
		if(top) inter[top]=intersectx(line[stk[top-1]],line[i]);
		stk[top++]=i;
	}

	for(int i=0;i<top;i++) ans[i]=line[stk[i]].id;
	sort(ans,ans+top);
	for(int i=0;i<top;i++) printf("%d ",ans[i]);
	puts("");

	return 0;
}