//FJOI2007 轮状病毒 组合数学+高精度
//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 105
using namespace std;

struct HI {
	char bits[105];
	int len;
	HI(long long val=0) {
		memset(bits,0,sizeof(bits));
		for(len=0;val;len++) {
			bits[len]=val%10;
			val/=10;
		}
	}
	HI operator +(const HI &rhs) {
		HI res;
		int ml=max(len,rhs.len);
		int ovf=0,tmp;
		for(int i=0;i<ml;i++) {
			tmp=ovf+bits[i]+rhs.bits[i];
			ovf=tmp/10;
			res.bits[i]=tmp%10;
		}
		if(ovf) res.bits[ml++]=ovf;
		res.len=ml;
		return res;
	}
	HI operator *(long long x) {
		HI res;
		int l=len;
		long long ovf=0,tmp;
		for(int i=0;i<len;i++) {
			tmp=1LL*bits[i]*x+ovf;
			res.bits[i]=tmp%10;
			ovf=tmp/10;
		}
		while(ovf) {
			res.bits[l++]=ovf%10;
			ovf/=10;
		}
		res.len=l;
		return res;
	}
	void out() {
		for(int i=len-1;i>=0;i--) putchar(bits[i]+'0');
		putchar('\n');
	}
};

HI dp[N];

int main()
{
	int n;
	HI ans=0;
	scanf("%d",&n);
	dp[0]=dp[1]=1;
	for(int i=2;i<n;i++)  {
		dp[i]=i;
		for(int j=1;j<i;j++) {
			dp[i]=(dp[i]+dp[j]*(i-j));
		}
		//cout<<dp[i]<<endl;
	}
	for(int i=1;i<=n;i++) {
		ans=(ans+dp[n-i]*i*i);
	}
	ans.out();
	return 0;
}