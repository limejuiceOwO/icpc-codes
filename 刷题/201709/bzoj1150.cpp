#include <cstdio>
#include <algorithm>
#include <queue>
#define N 100005
using namespace std;
typedef pair<long long,int> pii;

long long w[N];
int pre[N],nxt[N];
char vis[N];

void del(int pos)
{
	if(!pos) return;
	pre[nxt[pos]]=pre[pos];
	nxt[pre[pos]]=nxt[pos];
	vis[pos]=1;
}

int main()
{
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	int n,k,last;
	scanf("%d%d%d",&n,&k,&last);
	for(int i=1,pos;i<n;i++) {
		scanf("%d",&pos);
		pq.push(make_pair(w[i]=pos-last,i));
		pre[i]=i-1;
		nxt[i]=i+1;
		last=pos;
	}
	nxt[n-1]=0;

	long long ans=0;
	for(int kk=0;kk<k;kk++) {
		pii cur=pq.top();
		int pos=cur.second;
		pq.pop();

		if(vis[pos]) {
			kk--;
			continue;
		}

		ans+=w[pos];
		bool mark=false;
		if(pre[pos]!=0&&nxt[pos]!=0)
			pq.push(make_pair(w[pos]=w[pre[pos]]+w[nxt[pos]]-w[pos],pos));
		else
			mark=true;

		del(pre[pos]);
		del(nxt[pos]);
		if(mark) del(pos);
	}

	printf("%lld\n",ans);
	return 0;
}