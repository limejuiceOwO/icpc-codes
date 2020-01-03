//双栈排序 暴搜+贪心（？）
#include <iostream>
#include <algorithm>
#define N 1005
using namespace std;

int arr[N],s1[N],s2[N];
int n;
char ans[N];

bool solve(int p,int q,int d,int d1,int d2)
{
	if(p>n) return true;
	if(d1>0&&s1[d1-1]==p) {
		ans[d]='b';
		if(solve(p+1,q,d+1,d1-1,d2)) return true;
	}
	if(d2>0&&s2[d2-1]==p) {
		ans[d]='d';
		if(solve(p+1,q,d+1,d1,d2-1)) return true;
	}
	if(q<n&&(d1==0||s1[d1-1]>arr[q])) {
		ans[d]='a';
		s1[d1]=arr[q];
		if(solve(p,q+1,d+1,d1+1,d2)) return true;
	}
	if(q<n&&(d2==0||s2[d2-1]>arr[q])) {
		ans[d]='c';
		s2[d2]=arr[q];
		if(solve(p,q+1,d+1,d1,d2+1)) return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++) cin>>arr[i];
	if(solve(1,0,0,0,0)) {
		for(int i=0;i<2*n-1;i++) {
			cout<<ans[i]<<" ";
		}
		cout<<ans[2*n-1]<<endl;
	} else cout<<"0"<<endl;
	return 0;
}