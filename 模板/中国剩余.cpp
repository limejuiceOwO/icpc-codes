#include <iostream>
#define N 1005
using namespace std;
int p[N],a[N];

int extgcd(int a,int b,int &x,int &y)
{
	if(b==0) {
		x=1;y=0;return a;
	}
	int ret=extgcd(b,a%b,y,x);
	y-=x*(a/b);
	return ret;
}

int inv(int x,int p)
{
	int a,b;
	extgcd(x,p,a,b);
	return a+p;
}

int china(int n,int *a,int *p)
{
	int M=1;
	for(int i=0;i<n;i++) {
		M*=p[i];
	}
	int ans=0;
	for(int i=0;i<n;i++) {
		ans+=inv(M/p[i],p[i])*(M/p[i])*a[i];
	}
	return ans%M;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>p[i]>>a[i];//p[i] coprimes each other
	}
	cout<<china(n,a,p)<<endl;
	return 0;
}