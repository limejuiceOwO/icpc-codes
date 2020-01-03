#include<bits/stdc++.h>
using namespace std;
int ufs[500];
struct Edge {
	int u,v,d;
	bool operator <(const Edge &rhs) const
	{
		return d>rhs.d;
	}
}edges[5000];

int root(int u)
{
	return ufs[u]==u?u:ufs[u]=root(ufs[u]);
}

void uni(int a,int b) 
{
	int ra=root(a),rb=root(b);
	if(ra!=rb) ufs[ra]=rb;
}

int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}

int main()
{
	int n,m,s,t;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int u,v,d;
		cin>>u>>v>>d;
		edges[i]=(Edge){u-1,v-1,d};
	}
	cin>>s>>t;
	s--;t--;
	sort(edges,edges+m);
	double md=1000000;
	int mu=1,ml=0;
	for(int up=0;up<m;up++) {
		for(int i=0;i<n;i++)
			ufs[i]=i;
		for(int lo=up;lo<m;lo++) {
			uni(edges[lo].u,edges[lo].v);
			if(root(s)==root(t)) {
				if(md>(double)edges[up].d/edges[lo].d) {
					md=(double)edges[up].d/edges[lo].d;
					mu=edges[up].d;
					ml=edges[lo].d;
				}
				break;
			}
		}
	}
	
	if(md==1000000)
		cout<<"IMPOSSIBLE"<<endl;
	else if(mu%ml==0)
		cout<<mu/ml<<endl;
	else {
		int g=gcd(mu,ml);
		cout<<mu/g<<'/'<<ml/g<<endl;
	}
	return 0;
}
