//��Ҫ2*m-1+3�Ŀռ䣬����2^m>=Ԫ�ظ��� 

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
