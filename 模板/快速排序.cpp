#include <bits/stdc++.h>
using namespace std;
int arr[100000];
/*
void quicksort(int *s,int *e)
{
	int key=*s;
	int *i=s,*j=e-1;
	if(j<=i) return;
	while(j>i) {
		while(j>i&&*i<=key) i++;
		while(j>i&&*j>key) j--;
		swap(*i,*j);
	}
	quicksort(s,i);
	quicksort(i+1,e);
	return;
}
*/

inline void swap(int *a,int *b)
{
	int t=*a;*a=*b;*b=t;
}

void quicksort(int *s,int *e)
{
	if(e-s<2) return;
	swap(s,s+rand()%(e-s-1));
	int *i=s+1;
	for(int *j=s+1;j<e;j++) {
		if(*j<*s) swap(i++,j);
	}
	swap(s,i-1);
	quicksort(s,i-1);
	quicksort(i,e);
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	quicksort(arr,arr+n);
	for(int i=0;i<n;i++)
	  cout<<arr[i]<<' ';
	cout<<endl;
	return 0;
}
