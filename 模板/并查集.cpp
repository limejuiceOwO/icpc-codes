int rt[N];

int root(int u)
{
	return (rt[u] == u) ? u : (rt[u] = root(rt[u]));
}

void merge(int u,int v)
{
	if(root(u) != root(v))
		rt[rt[u]] = rt[v];
}

int main()
{
	for(int i = 1;i <= n;i++)
		rt[i] = i;
	//...
}