#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

struct Answer {
	int a,b,w;
	bool operator <(const Answer &rhs) const {
		return b==rhs.b ? a<rhs.a : b<rhs.b;
	}
	bool operator ==(const Answer &rhs) const {
		return a==rhs.a&&b==rhs.b;
	}
}answer[N];

int dp[N];

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;

	int cnt=1;
	for(int i=0;i<n;i++) {
		int a,b;
		cin>>b>>a;
		if(a+b+1>n) continue;
		answer[cnt++]={a,n-b-1,0};
	}

	answer[0]={-1,-1,0};
	sort(answer,answer+cnt);

	int c=1;
	for(int i=1;i<cnt;c++) {
		int j=i,w=1;
		while(j<cnt-1&&answer[j]==answer[j+1]) j++,w++; //是j不是i！
		answer[c]=answer[i];
		answer[c].w=min(answer[c].b-answer[c].a+1,w);
		i=j+1;
	}
	cnt=c;

	for(int i=1;i<cnt;i++) {
		int l=1,r=i;
		while(l<r) {
			int mid=(l+r)>>1;
			if(answer[mid].b<answer[i].a)
				l=mid+1;
			else
				r=mid;
		}
		dp[i]=max(dp[i-1],dp[l-1]+answer[i].w);
	}

	cout<<n-dp[cnt-1]<<endl;

	return 0;
}