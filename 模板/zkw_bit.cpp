//需要2*m-1+3的空间，其中2^m>=元素个数 

int qur(int *tree,int r) //[1,r)
{
  int ans=0;
  for(r+=n;r;r>>=1) {
    if(r&1) ans+=tree[r^1];
  }
  return ans;
}

void alter(int *tree,int idx,int delta)
{
  for(idx+=n;idx;idx>>=1) tree[idx]+=delta;
}
