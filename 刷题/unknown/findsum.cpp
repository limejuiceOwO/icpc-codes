#include<bits/stdc++.h>
#define N 1000
using namespace std;
int arr[N];

int main()
{
	int n,x;
	scanf("%d%d",&n,&x);
	for(int i=0;i<n;i++) scanf("%d",arr+i);
	for(int i=0,j=n-1;i<=j;i++) {
	  while(arr[i]+arr[j]>x) j--;
	  if(arr[i]+arr[j]==x) {
	    puts("YES");
	    break;
    }
  }
	return 0;
}
