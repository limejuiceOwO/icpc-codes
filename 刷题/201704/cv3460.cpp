#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

inline int gcd(int a,int b)
{
	while(b!=0) {
		int t=b;b=a%b;a=t;
	}
	return a;
}

int main()
{
	int a,b,l;
	cin>>a>>b>>l;
	double m=(double)a/b,mioffset=100000;
	int i=1,mi=0,mj=0,g=gcd(a,b);
	if(a/g<=l&&b/g<=l) {
		cout<<a/g<<" "<<b/g<<endl;
		return 0;
	}
	while(i<=l&&floor(m*i)+1<=l) {
		int cur=floor(m*i)+1;
		double offset=(double)cur/i-m;
		//assert(offset>0);
		//cout<<i<<" "<<cur<<" "<<offset<<endl;
		if(mioffset>offset) {
			mioffset=offset;
			mi=i,mj=cur;
		}
		i++;
	}
	g=gcd(mi,mj);
	cout<<mj/g<<" "<<mi/g<<endl;
	return 0;
}