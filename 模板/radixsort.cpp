#include <iostream>
#include <algorithm>
#include <cstring>
#define N 10005
using namespace std;

int arr[N],tmp[N];
int cnt[11];

void radixsort(int *s,int *e)
{
	int n=e-s;
	int *t1=s,*t2=tmp;
	int p=1;
	while((*s)/p>0) {
		//for(int i=0;i<n;i++) cout<<t1[i]<<" ";
		//cout<<endl;
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;i++) {
			cnt[t1[i]/p%10]++;
		}
		for(int i=1;i<10;i++) {
			cnt[i]+=cnt[i-1];
		}
		for(int i=n-1;i>=0;i--) {
			t2[--cnt[t1[i]/p%10]]=t1[i];
		}
		swap(t1,t2);
		p*=10;
	}
	if(t1!=s) memcpy(s,t1,sizeof(arr));
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) cin>>arr[i];
	radixsort(arr,arr+n);
	for(int i=0;i<n;i++) cout<<arr[i]<<" ";
	return 0;
}