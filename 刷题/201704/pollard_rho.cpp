#include <iostream>
#include <algorithm>
#define S 13 
using namespace std;

const int sample[S]={2,3,5,7,11,13,17,23,31,37,41,43,47,};
long long a,b;

long long qmul(long long a,long long b,long long m)
{
	//return (long long)a*b-(long double)(a/m)*b;
	return a*b%m;
}

long long qpow(long long a,long long p,long long m)
{
	long long ret=1;
	while(p) {
		if(p&1) ret=qmul(ret,a,m);
		a=qmul(a,a,m);
		p>>=1;
	}
	return ret;
}

bool miller(long long x)
{
	long long n=x-1;
	if(!n) return false;
	while(~n&1) n>>=1;
	for(int i=0;i<S;i++) {
		if(sample[i]==x) return true;
		if(qpow(sample[i],x-1,x)!=1LL) return false;
		long long pre=qpow(sample[i],n,x);
		for(int k=n;k<x-1;k<<=1) { 
			long long b=qmul(pre,pre,x);
			if(b==1&&pre!=1&&pre!=x-1) return false;
			pre=b;
		}
	}
	return true;
}

long long gcd(long long a,long long b)
{
	while(b!=0) {
		long long t=a;
		a=b;
		b=t%b;
	}
	return a;
}

long long f(long long x)
{
	return x*(x+2)+3;
}

void rho(long long x)
{
	if(x==1) return;
	if(miller(x)) {
		cout<<x<<endl;
		return;
	}
	while(1)
	{
		long long g;
		a=f(a),b=f(f(b));
		if(a==b) a=rand(),b=rand();
		if((g=gcd(abs(a-b),x))!=1) {
			rho(x/g);
			rho(g);
			return;
		}
	}
}

int main()
{
	while(1) {
		long long x;
		cin>>x;
		rho(x);
		//cout<<miller(x)<<endl;
	}
	return 0;
}