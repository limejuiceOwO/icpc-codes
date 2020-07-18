int sparse[LOGN][N];

void build_table(int n)
{
	for(int i = 1;(1 << i) < n;++i) {
		for(int j = 0;j < n;++j) {
			sparse[i][j] = sparse[i - 1][j];
			if(j + (1 << (i - 1)) < n) {
				sparse[i][j] = min(sparse[i][j],sparse[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
}

int query(int lb,int rb)
{
	int lg = 0;
	while((1 << lg) <= (rb - lb + 1))
		++lg;
	--lg;
	return min(sparse[lg][lb],sparse[lg][rb - (1 << lg) + 1]);
}