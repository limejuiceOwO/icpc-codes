#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

long long gcd(long long a,long long b)
{
	while(b) {
		long long t=b;
		b=a%b;
		a=t;
	}
	return a;
}

long long solve(long long x) //a^2+b^2=x,(a,b)=1
{
	//cout<<x<<" ";
	long long ans=0;
	long long bound=sqrt(x)+1;

	for(long long a=1;a<bound;a++) {
		long long b=sqrt(x-a*a);
		if(b>0&&a*a+b*b==x&&a<b&&gcd(a,b)==1)
			ans++;
	}

	//cout<<ans<<endl;
	return ans;
}

int main()
{
	long long r;
	scanf("%lld",&r);
	r*=2;

	long long ans=0;
	long long bound=(long long)sqrt(r)+1;
	for(long long i=1;i<bound;i++) { //i*i*p*q
		if(r%i==0) {
			//long long sq=sqrt(i);
			//if(sq*sq==i)
			ans+=solve(r/i);
			if(i!=r/i) {
				ans+=solve(i);
			}
		}
	}

	printf("%lld\n",ans*4+4);
	return 0;
}