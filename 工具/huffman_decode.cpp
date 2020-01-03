#include<bits/stdc++.h>
#define BITSIZE 256
using namespace std;

struct Node {
	int lch,rch;//lch=0,rch=1
	//lch=-1,rch=character
} tree[BITSIZE*2];

bool getbit(FILE *input)
{
	const static unsigned char mask=(1<<7);
	static unsigned char buf;
	static int k=8;
	if(k==8) {
		k=1;
		buf=fgetc(input);
	} else {
		buf<<=1;
		k++;
	}
	return buf&mask;
}

char decode(int p,FILE *input)
{
	while(tree[p].lch>=0)
		p=(getbit(input)?tree[p].rch:tree[p].lch);
	return tree[p].rch;
}

int main(int argc,char *argv[])
{
	FILE *input,*output;
	int treesize;
	size_t cnt;
	if(argc!=3) return 2;
	if((input=fopen(argv[1],"rb+"))==NULL||(output=fopen(argv[2],"wb+"))==NULL) return 2;
	fread(&cnt,sizeof(size_t),1,input);
	fread(&treesize,sizeof(int),1,input);
	printf("%d %d\n",cnt,treesize);
	fread(tree,sizeof(Node),treesize,input);
	while(cnt--)
		fputc(decode(treesize-1,input),output);
	fclose(input);
	fclose(output);
	return 0;
}
