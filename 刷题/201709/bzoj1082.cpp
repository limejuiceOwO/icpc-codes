#include <cstdio>
#include <functional>
#include <algorithm>
#include <cstring>
#define N 55
#define M 1005
using namespace std;

int arr1[N],arr2[M],sarr2[M],board[N];
int n,m,mid,sum,tot;

bool solve(int cur=m-mid)
{
	if(cur==m) return true;

	int abd=0;
	for(int i=0;i<n;i++) {
		if(board[i]<arr2[m-1])
			abd+=board[i];
	}
	if(abd+sum>tot) return false;

	for(int i=0;i<n;i++) {
		int mxsize=0;
		if(board[i]>=arr2[cur]&&board[i]>mxsize) {
			board[i]-=arr2[cur];
			if(solve(cur+1)) return true;
			mxsize=max(mxsize,board[i]);
			board[i]+=arr2[cur];
		}
	}
	return false;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		scanf("%d",&arr1[i]);
		tot+=arr1[i];
	}

	scanf("%d",&m);
	for(int i=0;i<m;i++) {
		scanf("%d",&arr2[i]);
	}

	sort(arr1,arr1+n);
	sort(arr2,arr2+m,greater<int>());

	for(int i=1;i<=m;i++) {
		sarr2[i]=arr2[i-1]+sarr2[i-1];
	}

	int lb=1,rb=m+1;
	while(lb<rb) {
		mid=(lb+rb)>>1;
		//cout<<mid<<endl;
		sum=sarr2[m]-sarr2[m-mid];
		memcpy(board,arr1,sizeof(arr1));
		if(solve()) {
			lb=mid+1;
		} else {
			rb=mid;
		}
	}

	printf("%d\n",lb-1);
	return 0;
}