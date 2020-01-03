#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
using namespace std;
map<long long,int> beyond;
long long x,k,z;
long long x2;

long long f(long long xx)
{
	return (x*xx)%z;
}

long long f2(long long xx)
{
	return (x2*xx)%z;
}

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		cin>>x>>z>>k; //x^y=k mod z
		if(x==0&&k==0&&z==0)
			break;

		long long step=min(ceil(sqrt(z)),1000.0),cycle=step;
		long long p=k,p2=k;

		beyond.clear();
		for(int i=1;i<=step;i++) {
			beyond[p]=i; //i-1
			p=f(p);
			p2=f(f(p2));

			if(p==p2) {
				cycle=i;
				break;
			}
		}

		x2=1;
		for(int i=0;i<step;i++)
			x2=(x2*x)%z;

		int cnt=0;
		p=p2=1;

		while(1) {
			if(beyond[p]&&step*cnt-beyond[p]+1>=0) {
				int z=step*cnt;
				//for(int k=0;beyond[p]+k*cycle<step&&z-beyond[p]+1>=0;k++)
				//	z-=cycle;
				//z+=cycle;
				cout<<z-beyond[p]+1<<endl;
				break;
			}

			if(cnt&&p==p2) {
				cout<<"No Solution"<<endl;
				break;
			}

			p=f2(p);
			p2=f2(f2(p2));
			cnt++;
			cout<<p<<" "<<beyond[p]<<endl;
		}
	}

	return 0;
}