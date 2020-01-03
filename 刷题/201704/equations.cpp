#include <iostream>
#include <algorithm>

using namespace std;

long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0) {
		x=1;y=0;return a;
	}
	long long g=exgcd(b,a%b,y,x);
	y-=x*(a/b);
	return g;
}

int main()
{
	int T,n;
	cin>>T;
	while(T--) {
		long long p,b;
		bool ok=true;
		cin>>n;
		cin>>p>>b;n--;
		b=(p-b)%p;
		while(n--) {
			long long p2,b2,x,y;
			cin>>p2>>b2;
			b2=(p2-b2)%p2;
			long long g=exgcd(p,p2,x,y);
			if((b2-b)%g!=0) ok=false;
			long long pp=p;
			p=p*p2/g;
			b=(pp*x*(b2-b)/g+b)%p;
			//cout<<p<<" "<<b<<endl;
		}
		if(ok) {
			if(b<0) cout<<b+p<<endl;
			else cout<<b<<endl;
		} else {
			cout<<"-1"<<endl;
		}
	}
	return 0;
}