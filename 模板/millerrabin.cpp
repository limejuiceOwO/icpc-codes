#include <iostream>
#include <cstdlib>
#define S 12
using namespace std;

int sample[S]={2,3,5,7,11,13,17,23,29,31,37,43,};

long long mul(long long a,long long b,long long p)
{
	//return a*b-(long long)((long double)a/p*b)*p;
	return a*b%p;
}

long long pow(long long a,long long m,long long p)
{
	long long ret=1;
	while(m) {
		if(m&1) ret=mul(ret,a,p);
		a=mul(a,a,p);
		m>>=1;
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
		if(pow(sample[i],x-1,x)!=1LL) return false;
		long long pre=pow(sample[i],n,x);
		for(int k=n;k<x-1;k<<=1) { //if b^k%x=1 and x is prime then b^(k/2)%x=1 or x-1
			long long b=mul(pre,pre,x); //so if b^k%x!=1 or p-1 then b^2k!=1
			if(b==1&&pre!=1&&pre!=x-1) return false;
			pre=b;
		}
	}
	return true;
}

int main()
{
	long long x;
	while(1)
	{
		cin>>x;
		cout<<miller(x)<<endl;
	}
}