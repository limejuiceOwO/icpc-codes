#include <iostream>
#define N 10005
using namespace std;
int arr[N];

int unique(int *s,int *e)
{
	int *pp=s;
	for(int *p=s+1;p<e;p++) {
		if(*p!=*pp) *(++pp)=*p;
	}
	return pp-s+1;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) cin>>arr[i];
	cout<<unique(arr,arr+n)<<endl;
	for(int i=0;i<n;i++) cout<<arr[i]<<" ";
	return 0;
}