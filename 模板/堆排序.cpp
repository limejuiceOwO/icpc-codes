int arr[10000];

void keep(int *s,int *e)
{
	int *cur=s,*maxp=s;
	while(s<e) {
		int *left=cur+(cur-s)*2+1,*right=left+1;
		if(left<e&&*left>*maxp) maxp=left;
		if(right<e&&*right>*maxp) maxp=right;
		if(maxp==cur) break;
		std::swap(*maxp,*cur);
		cur=maxp;
	}
}

void heapsort(int *s,int *e)
{
	for(int *i=s+(e-s)/2;i>=s;i--)
		keep(i,e);
	for(int *i=e-1;i>=s;i--) {
		swap(*i,*s);
		keep(s,i);
	}
}
