#include<bits/stdc++.h>
#define BITSIZE 256
using namespace std;

unsigned long long frq[BITSIZE];
typedef pair<unsigned long long,int> pii;
struct Node {
	int lch,rch;//lch=0,rch=1
	//lch=-1,rch=character
} tree[BITSIZE*2];
struct Code {
	char c[16];
	int size;
};

char bits[16];
Code table[BITSIZE];

void make_table(int p,int d)
{
	if(tree[p].lch<0) {
		unsigned char c=tree[p].rch;
		table[c].size=d;
		memcpy(table[c].c,bits,d);
	} else {
		bits[d]=0;
		make_table(tree[p].lch,d+1);
		bits[d]=1;
		make_table(tree[p].rch,d+1);
	}
}



int main(int argc,char *argv[])
{

	priority_queue<pii,vector<pii>,greater<pii> > pq;
	FILE *input,*output;
	if(argc!=3) return 2;
	if((input=fopen(argv[1],"rb+"))==NULL||(output=fopen(argv[2],"wb+"))==NULL) return 2;
	size_t cnt=0;
	int treesize=0;
	puts("Counting data...");
	while(1) {
		unsigned char c=fgetc(input);
		if(feof(input)) break;
		frq[c]++;
		cnt++;
	}
	puts("Building Huffman tree...");
	for(int i=0;i<BITSIZE;i++) {
		if(frq[i]) {
			tree[treesize]=(Node){-1,i};
			pq.push(make_pair(frq[i],treesize++));
		}
	}
	while(pq.size()>1) {
		pii p1=pq.top();pq.pop();
		pii p2=pq.top();pq.pop();
		int node1=p1.second,node2=p2.second;
		int f1=p1.first,f2=p2.first;
		tree[treesize]=(Node){node1,node2};
		pq.push(make_pair(f1+f2,treesize++));
	}
	puts("Making code table...");
	make_table(treesize-1,0);
	fseek(input,0,SEEK_SET);
	puts("Writing the tree into file...");
	fwrite(&cnt,sizeof(size_t),1,output);
	fwrite(&treesize,sizeof(int),1,output);
	fwrite(tree,sizeof(Node),treesize,output);
	puts("Encoding...");
	printf("%d %d\n",cnt,treesize);
	unsigned char data=0;
	int k=0;
	while(cnt--) {
		const Code &code=table[(unsigned char)fgetc(input)];
		for(int i=0;i<code.size;i++) {
			if(k==8) {
				k=1;
				fputc(data,output);
				data=code.c[i];
			} else {
				k++;
				data=(data<<1)+code.c[i];
			}
		}
	}
	fputc(data<<(8-k),output);
	fclose(input);
	fclose(output);
	return 0;
}
