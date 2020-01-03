#include<bits/stdc++.h>
#define HASH_SIZE 23333

int *hashtable[HASH_SIZE],*next[100000];
int data[100000];


int hash(int dat)
{
	return dat%HASH_SIZE;
	//return 0;
}

bool find(int dat)
{
	int h=hash(dat);
	int *p=hashtable[h];
	while(p) {
		if(dat==*p) return true;
		p=next[p-data];
	}
	return false;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) {
		int h;
		scanf("%d",data+i);
		h=hash(data[i]);
		next[i]=hashtable[h];
		hashtable[h]=data+i;
	}
	for(int i=0;i<m;i++) {
		int query;
		scanf("%d",&query);
		printf("%s\n",find(query)?"YES":"NO");
	}
	return 0;
}
