#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

int n,maxd;
ull mask[6][60];
int mcnt[6];

int pos(int i,int j,int type) //0横1竖
{
	return (2*n+1)*i+type*n+j;
}

int f(ull st)
{
	int cnt=0;
	for(int i=0;i<mcnt[n];i++) {
		if((st&mask[n][i])==mask[n][i]) {
			cnt++;
			st&=~mask[n][i];
		}
	}
	return cnt;
}

bool dfs(ull st,int d)
{
	if(d+f(st)>maxd) return false;

	ull vis=0;
	for(int i=0;i<mcnt[n];i++) {
		if((st&mask[n][i])==mask[n][i]) {
			for(int j=0;j<60;j++) {
				if((mask[n][i]&(1ULL<<j))&&!(vis&(1ULL<<j))) {
					vis|=(1ULL<<j);
					if(dfs(st&~(1ULL<<j),d+1)) {
						//cout<<"'"<<j<<endl;
						return true;
					}
				}
			}
			return false;
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);

	for(n=2;n<=5;n++) {
		for(int l=1;l<=n;l++) {
			for(int i=0;i<=n-l;i++) {
				for(int j=0;j<=n-l;j++) {
					for(int k=i;k<i+l;k++) {
						mask[n][mcnt[n]]|=(1ULL<<pos(k,j,1));
						mask[n][mcnt[n]]|=(1ULL<<pos(k,j+l,1));
					}
					for(int k=j;k<j+l;k++) {
						mask[n][mcnt[n]]|=(1ULL<<pos(i,k,0));
						mask[n][mcnt[n]]|=(1ULL<<pos(i+l,k,0));
					}
					mcnt[n]++;
				}
			}
		}
	}
	
	int t;
	cin>>t;
	while(t--) {
		int k;
		cin>>n>>k;


		ull s=0;
		for(int i=0;i<k;i++) {
			int pos;
			cin>>pos;
			s|=(1ULL<<(pos-1));
		}
		s=~s;

		for(maxd=0;maxd<60;maxd++) {
			if(dfs(s,0)) {
				cout<<maxd<<endl;
				goto out;
			}
		}

		cout<<"FaQ"<<endl;
		out:while(0);
	}
	return 0;
}