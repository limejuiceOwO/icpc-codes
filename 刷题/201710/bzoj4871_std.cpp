#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=200010,oo=100000000;
int fir[maxn],ne[maxn],to[maxn],deg[maxn],
f[maxn],g[maxn],h[maxn],vis[maxn],
n,X;
int rd()
{
	int x=0;
	char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
void add(int num,int u,int v)
{
	ne[num]=fir[u];
	fir[u]=num;
	to[num]=v;
}
void dp(int e)
{
	if (vis[e]) return;
	int u=to[e],f1=-oo,f2=-oo;
	vis[e]=1;
	h[e]=-oo;
	for (int i=fir[to[e]];i;i=ne[i])
		if (i!=(e^1))
		{
			dp(i);
			h[e]=max(h[e],g[i]);
			if (f[i]>=f1)
			{
				f2=f1;
				f1=f[i];
			}
			else f2=max(f2,f[i]);
		}
	f[e]=max(deg[u]-1,f1+deg[u]-2);
	g[e]=max(f[e],f1+f2+deg[u]-3);
	h[e]=max(h[e],g[e]);
}
void solve()
{
	int u,v,f1,f2,f3,f4,h1,h2,ans=0;
	n=rd();
	if (X) rd(),rd();
	if (X==2) rd(),rd();
	for (int i=1;i<=n;i++) fir[i]=deg[i]=0;
	for (int i=1;i<n;i++)
	{
		u=rd();
		v=rd();
		deg[u]++;
		deg[v]++;
		add(i<<1,u,v);
		add(i<<1|1,v,u);
		vis[i<<1]=vis[i<<1|1]=0;
	}
	for (int i=1;i<=n;i++)
	{
		f1=f2=f3=f4=h1=h2=-oo;
		for (int j=fir[i];j;j=ne[j])
		{
			dp(j);
			ans=max(ans,h[j]+1);
			if (vis[j^1]) ans=max(ans,h[j]+h[j^1]);
			if (f[j]>=f1)
			{
				f4=f3;
				f3=f2;
				f2=f1;
				f1=f[j];
			}
			else
			{
				if (f[j]>=f2)
				{
					f4=f3;
					f3=f2;
					f2=f[j];
				}
				else
				{
					if (f[j]>=f3)
					{
						f4=f3;
						f3=f[j];
					}
					else f4=max(f4,f[j]);
				}
			}
			if (h[j]>=h1)
			{
				h2=h1;
				h1=h[j];
			}
			else h2=max(h2,h[j]);
		}
		ans=max(ans,h1+h2+1);
		ans=max(ans,f1+f2+f3+deg[i]-3);
		ans=max(ans,f1+f2+f3+f4+deg[i]-4);
	}
	printf("%d\n",ans);
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	T=rd();
	X=rd();
	while (T--) solve();
}