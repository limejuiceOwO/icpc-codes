#include <iostream>
#include <algorithm>
#include <cmath>
#define N 300005
using namespace std;

int arr[N];
int cnt[N],out[N],lz[N],blknum[N];
int n;

inline void update(int i)
{
	if(i+arr[i]>n||blknum[i+arr[i]]!=blknum[i]) {
		cnt[i]=1;
		out[i]=i+arr[i];
	} else {
		cnt[i]=cnt[i+arr[i]]+1;
		out[i]=out[i+arr[i]]; 
	}
}

int main()
{
	ios::sync_with_stdio(false);

	int q,t;
	cin>>n>>q>>t;

	/*
	int sq=sqrt(n);
	for(int i=0;i<n;i++) {
		blknum[i]=i/sq;
	}
	*/
	
	int j=0;
	for(int i=0,k=0;i<n;i++,k++) {
		blknum[i]=j;
		if(k>=j) {
			j+=20;
			k=0;
		}
	}
	cout<<j<<endl;

	for(int i=0;i<=n;i++) {
		cin>>arr[i];
	}
	for(int i=n;i>=0;i--) {
		update(i);
	}

	int ans[2]={0,0};
	long long tot=0;
	for(int kase=1;kase<=q;kase++) {
		int op,a,b;
		cin>>op;
		if(op==1) {
			cin>>a>>b;
			arr[a]=b;
			lz[blknum[a]]=max(lz[blknum[a]],a);
		} else if(op==2) {
			cin>>a;
			int cans=0;
			while(a<=n) {
				for(int &i=lz[blknum[a]];i>=a;i--) {
					update(i);
				}
				cans+=cnt[a];
				a=out[a];
			}
			if(t==1) {
				ans[kase&1]^=cans;
				tot+=cans;
			} else if(t==2) {
				cout<<cans<<endl;
			}
		}
	}

	if(t==1) {
		cout<<ans[1]<<endl;
		cout<<ans[0]<<endl;
		cout<<tot<<endl;
	}

	return 0;
}