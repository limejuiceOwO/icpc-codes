#include <iostream>
#include <algorithm>
#include <cstring>
#define N 255
#define MOD 105
using namespace std;

struct BigInt {
	int top;
	int val[N];
	BigInt ()
	{
		top=0;
		memset(val,0,sizeof(val));
	}
	BigInt operator *(int v)
	{
		BigInt ret;
		int ovf=0;
		ret.top=top;
		for(int i=0;i<ret.top;i++) {
			int x=ovf+val[i]*v;
			ovf=x/10;
			ret.val[i]=x%10;
		}
		while(ret.top<MOD&&ovf) {
			ret.val[ret.top++]=ovf%10;
			ovf/=10;
		}
		while(ret.val[ret.top-1]==0) ret.top--;

		return ret;
	}
	BigInt operator *(const BigInt &rhs)
	{
		BigInt ret;
		ret.top=min(MOD,top+rhs.top+2);
		for(int i=0;i<ret.top;i++) {
			for(int j=0;j<=i;j++) {
				ret.val[i]+=val[j]*rhs.val[i-j];
			}
		}

		int ovf=0;
		for(int i=0;i<ret.top;i++) {
			int x=ovf+ret.val[i];
			ovf=x/10;
			ret.val[i]=x%10;
		}
		while(ret.top<MOD&&ovf) {
			ret.val[ret.top++]=ovf%10;
			ovf/=10;
		}
		while(ret.val[ret.top-1]==0) ret.top--;

		return ret;
	}
};

char arr[N];

int main()
{
	ios::sync_with_stdio(false);

	int k;
	cin>>arr>>k;

	BigInt x;
	int len=strlen(arr);
	for(int i=0;i<min(k,len);i++) {
		x.val[i]=arr[len-i-1]-'0';
	}
	x.top=min(k,len);//注意top不能大

	BigInt z=x,ans;
	ans.val[0]=ans.top=1;

	for(int i=0;i<k;i++) {
		int j;
		BigInt p=z;
		for(j=0;j<10;j++) {
			if((p*x).val[i]==x.val[i]) {
				ans=ans*(j+1);
				break;
			}
			p=p*z;
		}

		if(j==10) {
			cout<<"-1"<<endl;
			return 0;
		}
		z=p;
	}

	for(int i=ans.top-1;i>=0;i--) cout<<ans.val[i];
	cout<<endl;
	return 0;
}