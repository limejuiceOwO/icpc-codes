#include <cstdio>
#include <algorithm>
#define N 15005
#define NN 32773
using namespace std;

int val[NN],ans[N];
int n;

void alt(int pos)
{
	while(pos<NN) {
		val[pos]++;
		pos+=(pos&-pos);
	}
}

int qur(int pos)
{
	int ans=0;
	while(pos) {
		ans+=val[pos];
		pos-=(pos&-pos);
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		alt(x+1);
		ans[qur(x+1)]++;
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}