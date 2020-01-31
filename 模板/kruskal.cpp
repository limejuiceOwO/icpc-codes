#include <vector>
#include <algorithm>

int rt[N];
typedef struct Edge
{
	int u,v,w;
	bool use = false;
	bool operator <(const Edge &rhs) const {
		return w < rhs.w;
	}
} Edge;
vector<Edge> edges;
typedef vector<Edge>::iterator Iter;

int root(int u)
{
	return (rt[u] == u) ? u : (rt[u] = root(rt[u]));
}

void merge(int u,int v)
{
	if(root(u) != root(v))
		rt[rt[u]] = rt[v];
}

int kruskal(vector<Edge> &edges)
{
	int sum_weight = 0;
	sort(edges.begin(),edges.end());
	for(Iter it = edges.begin();it != edges.end();++it) {
		Edge &e = *it;
		if(root(e.u) != root(e.v)) {
			merge(e.u,e.v);
			e.use = true;
			sum_weight += e.w;
		}
	}
	return sum_weight;
}

int main()
{
	//edges input
	for(int i = 1;i <= n;i++)
		rt[i] = i;
	kruskal(edges);
	//...
}