#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 1000005
#define NN 67108800
using namespace std;

char val[NN];
char bits[N*30],nbits[N*30];
int n,b;

int qur(int pos,int lb=0,int rb=b,int p=1)
{
	if(lb==rb) {
		return val[p];
	}
	int mid=(lb+rb)>>1;
	if(pos>mid) {
		int res=qur(pos,mid+1,rb,p<<1|1);
		return res ? res : val[p<<1];
	} else {
		return qur(pos,lb,mid,p<<1);
	}
}

void alt(int pos,int v,int lb=0,int rb=b,int p=1)
{
	if(lb==rb) {
		val[p]=v;
		return;
	}

	int mid=(lb+rb)>>1;
	if(pos>mid)
		alt(pos,v,mid+1,rb,p<<1|1);
	else
		alt(pos,v,lb,mid,p<<1);
	val[p]=val[p<<1|1] ? val[p<<1|1] : val[p<<1];
}

void add(char *arr,int v,int k)
{
	char ovf=0;
	for(int i=k;i<N*30&&(v||ovf);i++) {
		char b=arr[i],prev=bits[i]-nbits[i];
		arr[i]=(b+ovf+(v&1))&1;
		ovf=((b+ovf+(v&1))>>1)&1;
		v>>=1;

		if(bits[i]-nbits[i]!=prev)
			alt(i,bits[i]-nbits[i]);
	}
}

int main()
{
	scanf("%d%*d%*d%*d",&n);
	b=max(105,30*n+40);

	while(n--) {
		int cmd,v,k;
		scanf("%d",&cmd);
		if(cmd==1) {
			scanf("%d%d",&v,&k);
			if(v<0) {
				add(nbits,-v,k);
			} else {
				add(bits,v,k);
			}
		} else if(cmd==2) {
			scanf("%d",&k);
			int ans=bits[k]^nbits[k];
			if(k>0&&qur(k-1)==-1) ans^=1;
			printf("%d\n",ans);
		}
	}

	return 0;
}