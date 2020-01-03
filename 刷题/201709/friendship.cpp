#include <iostream>
#include <algorithm>
#include <cstring>
#define N 500005
#define NN 1048581
#define INF 1000000000005LL
using namespace std;

long long val1[NN],val2[NN];
long long arr1[N],arr2[N],f[N];
int n;

long long qur(long long *tr,int l,int r,int lb=0,int rb=n,int p=1)
{
	if(l>rb||r<lb) return INF;
	if(l<=lb&&r>=rb) return min(tr[p],INF);
	int mid=(lb+rb)>>1;
	return min(qur(tr,l,r,lb,mid,p<<1),qur(tr,l,r,mid+1,rb,p<<1|1));
}

void alt(long long *tr,int pos,long long val)
{
	int lb=0,rb=n,p=1;
	while(lb<rb) {
		tr[p]=min(tr[p],val);

		int mid=(lb+rb)>>1;
		if(pos>mid) {
			p=p<<1|1;
			lb=mid+1;
		} else {
			p=p<<1;
			rb=mid;
		}
	}
	tr[p]=min(tr[p],val);
}

int main()
{
	ios::sync_with_stdio(false);

	int k;
	cin>>n>>k;

	for(int i=1;i<=n;i++) {
		cin>>arr1[i];
		arr1[i]+=arr1[i-1];
	}
	for(int i=0;i<n;i++) {
		cin>>arr2[i];
	}

	memset(val1,0x7f,sizeof(val1));
	memset(val2,0x7f,sizeof(val2));
	f[n]=0;
	alt(val1,n,0);//税款
	alt(val2,n,arr1[n]);//路程
	for(int i=n-1;i>=0;i--) {
		int pos=lower_bound(arr1+i+1,arr1+n+1,arr1[i]+arr2[i])-arr1;
		long long q1=qur(val1,i+1,min(i+k,pos-1)),q2=qur(val2,pos,min(i+k,n));
		f[i]=INF;
		if(q1<INF) f[i]=min(q1+arr2[i],f[i]);
		if(q2<INF) f[i]=min(q2-arr1[i],f[i]);
		alt(val1,i,f[i]);
		alt(val2,i,f[i]+arr1[i]);
	}

	cout<<f[0]<<endl;
	return 0;
}