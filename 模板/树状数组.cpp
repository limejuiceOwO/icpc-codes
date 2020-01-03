#include<bits/stdc++.h>
#define P 16
using namespace std;

const int N=(1<<P)+10;
int bit[N];
int n;

void alter(int idx,int v)
{
	while(idx<=N) {
		bit[idx]+=v;
		idx+=(idx&-idx);
	}
}

int query(int k)
{
	int idx=0;
	if(k<1||bit[1<<P]<k) return -1;
	for(int len=(1<<(P-1));len>0&&idx<=N;len>>=1) {
		if(bit[idx+len]<k) {
			k-=bit[idx+len];
			idx+=len;
		}
	}
	return idx+1;
}
