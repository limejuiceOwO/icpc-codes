#include <iostream>
#include <algorithm>
#define N 25
using namespace std;

long long jc[N];

int main()
{
	jc[0]=jc[1]=1;
	for(int i=2;i<N;i++)
		jc[i]=jc[i-1]*i;

	while(1) { 
		int n;
		cin>>n;

		int tot=0;
		long long div=1;
		for(int i=2;i*i<=n;i++) {
			int cnt=0;
			while(n%i==0) {
				cnt++;
				n/=i;
			}
			tot+=cnt;
			div*=jc[cnt];
		}
		if(n>1) tot++;

		cout<<tot<<" "<<jc[tot]/div<<endl;
	}
	return 0;
}