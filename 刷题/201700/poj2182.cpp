#include<iostream>
#include<algorithm>
#define P 13
using namespace std;
const int N=(1<<P)+10;
int bit[N],arr[N],ans[N];

void alter(int idx,int v)
{
	while(idx>0&&idx<=N) {
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

int main()
{
  cin.sync_with_stdio(false);
  int n;
  cin>>n;
  for(int i=1;i<n;i++) {
    cin>>arr[i];
    alter(i,1);
  }
  alter(n,1);
  for(int i=n-1;i>=0;i--) {
    ans[i]=query(arr[i]+1);
    alter(ans[i],-1);
  }
  for(int i=0;i<n;i++) {
    cout<<ans[i]<<endl;
  }
  return 0;
}

