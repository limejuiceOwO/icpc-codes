#include <cstdio>
#include <algorithm>
#define N 200005
using namespace std;
long long pos[N],val[N];

int main()
{
	int n,top=0,cnt=0;
	long long d,lastans=0;
	scanf("%d%lld",&n,&d);
	while(n--) {
		char cmd[5];
		long long x;
		scanf("%s%lld",&cmd,&x);
		if(cmd[0]=='Q') {
			lastans=val[lower_bound(pos,pos+top,cnt-x)-pos];
			printf("%lld\n",lastans);
		} else if(cmd[0]=='A') {
			x=(lastans+x)%d;
			while(top&&val[top-1]<=x) top--;
			val[top]=x;
			pos[top++]=cnt++;
			//cout<<top<<" "<<cnt<<endl;
		}
	}

	return 0;
}