#include <iostream>
#include <algorithm>
#include <vector>
#define N 500005
#define M 250005
using namespace std;

vector<int> G[N];
int type[N],rub[N],fa[N],fin[N];

struct Qur {
	int id,u,v,type;
	bool operator <(const Qur &rhs) const {
		return u<rhs.u;
	}
} qur[M];
int ans[M];
int qcnt,mcnt;

void mark(int u)
{
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(!rub[v]) {
			rub[v]=1;
			mark(v);
		}
	}
}

int rt(int u)
{
	return fa[u]==u ? u : fa[u]=rt(fa[u]);
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;

	for(int i=1;i<=n;i++) {
		fa[i]=fin[i]=i;
	}

	for(int i=0;i<m;i++) {
		int cmd;
		cin>>cmd;
		if(cmd==0) {
			int cnt,v;
			int u=n+mcnt+1;
			cin>>type[u]>>cnt;
			fa[u]=u;
			for(int j=0;j<cnt;j++) {
				cin>>v;
				G[u].push_back(v);
			}
			mcnt++;
		} else {
			qur[qcnt].id=qcnt;
			cin>>qur[qcnt].u>>qur[qcnt].v;
			if(qur[qcnt].u<qur[qcnt].v) {
				swap(qur[qcnt].u,qur[qcnt].v);
				qur[qcnt].type=1; //0交1并
			}
			qcnt++;
		}
	}

	sort(qur,qur+qcnt);

	int p1=0,p2=n+1;
	while(p1<qcnt) {
		while(p1<qcnt&&p2>qur[p1].u) {
			if(qur[p1].u==qur[p1].v
				||(rt(qur[p1].v)==rt(qur[p1].u)&&qur[p1].type==type[qur[p1].u]&&!rub[qur[p1].v])
				||fin[qur[p1].u]==fin[qur[p1].v]) {
				ans[qur[p1].id]=1;
			} else {
				ans[qur[p1].id]=0;
			}
			p1++;
		}
		if(p1>=qcnt) break;

		if(p2<=n+mcnt) {
			if(G[p2].size()==1) {
				type[p2]=type[fin[G[p2][0]]];
				fin[p2]=fin[G[p2][0]];
			} else {
				fin[p2]=p2;
			}
			for(unsigned int i=0;i<G[p2].size();i++) {
				int v=G[p2][i];
				fa[v]=p2;
				if(type[fin[v]]!=type[p2])
					mark(fin[v]);
			}
			p2++;
		}
	}

	for(int i=0;i<qcnt;i++) {
		cout<<ans[i]<<endl;
	}

	return 0;
}