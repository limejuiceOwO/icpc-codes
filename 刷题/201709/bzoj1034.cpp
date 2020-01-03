#include <cstdio>
#include <algorithm>
#define N 100005
using namespace std;

int arr1[N],arr2[N];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		scanf("%d",&arr1[i]);
	}
	for(int i=0;i<n;i++) {
		scanf("%d",&arr2[i]);
	}

	sort(arr1,arr1+n);
	sort(arr2,arr2+n);

	int ans=0,p1=0,p2=n-1,p3=0,p4=n-1;
	while(p1<=p2) {
		if(arr1[p1]>arr2[p3]) {
			ans+=2;
			p1++,p3++;
		} else if(arr1[p2]>arr2[p4]) {
			ans+=2;
			p2--,p4--;
		} else {
			ans+=(arr1[p1]==arr2[p4]);
			p1++,p4--;
		}
	}
	printf("%d ",ans);

	ans=0,p1=0,p2=n-1,p3=0,p4=n-1;
	while(p1<=p2) {
		if(arr1[p1]<arr2[p3]) {
			p1++,p3++;
		} else if(arr1[p2]<arr2[p4]) {
			p2--,p4--;
		} else {
			ans+=2-(arr1[p2]==arr2[p3]);
			p2--,p3++;
		}
	}
	printf("%d\n",ans);
	return 0;
}