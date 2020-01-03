#include <iostream>
#include <algorithm>
#define N 105
using namespace std;

struct Course {
	int l,r,c;
	bool operator <(const Course &rhs) const {
		return r<rhs.r;
	}
} course[N];

int dp[N];
int mnd[N];
int quec[N],qued[N];
int cnt;

int main()
{
	ios::sync_with_stdio(false);

	int t,s,n;
	cin>>t>>s>>n;
	t--;

	course[0]=(Course) {-1,-1,1};
	for(int i=1;i<=s;i++) {
		cin>>course[i].l>>course[i].r>>course[i].c;
		course[i].r+=course[i].l-1;
	}

	for(int i=0;i<n;i++) {
		int c,d;
		cin>>c>>d;
		if(mnd[c])
			mnd[c]=min(mnd[c],d);
		else
			mnd[c]=d;
	}

	for(int i=0;i<N;i++) {
		if(!mnd[i]||(cnt&&qued[cnt-1]<mnd[i])) continue;
		qued[cnt]=mnd[i];
		quec[cnt++]=i;
	}

	sort(course,course+s+1);

	int ans=0;
	for(int i=0;i<=s;i++) {
		if(course[i].r>t)
			continue;
		for(int j=0;j<i;j++) {
			if(course[i].l>course[j].r) {
				int gap=course[i].l-course[j].r-1;
				int pos=upper_bound(quec,quec+cnt,course[j].c)-quec-1;
				if(pos>=0) {
					dp[i]=max(dp[i],dp[j]+(gap/qued[pos]));
				}
			}
		}

		int pos=upper_bound(quec,quec+cnt,course[i].c)-quec-1;
		ans=max(ans,dp[i]+(pos>=0 ? (t-course[i].r)/qued[pos] : 0));
	}

	cout<<ans<<endl;
	return 0;
}