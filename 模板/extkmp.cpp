#include <iostream>
#include <algorithm>
#include <cstring>
#include <assert.h>
#define N 10005
using namespace std;

int ans[N],next[N];
char S[N],B[N];

void extkmp(char *S,char *B,int *ans,int *next)
{
	int lens=strlen(S),lenb=strlen(B);
	int mx=0,mxi=1;
	next[0]=lenb;
	//while(mx<lenb-1&&B[mx]==B[mx+1]) mx++;
	//next[1]=mx;
	for(int i=1;i<lenb;i++) {
		if(next[i-mxi]<mx-i+1) {
			next[i]=next[i-mxi];
			continue;
		}
		int j=max(0,mx-i+1);
		while(i+j<lenb&&B[j]==B[i+j]) j++/*,assert(mx<i||(next[i-mxi]!=mx-i+1&&j==(mx-i+1)))*/; //猜想（？）如果next[i-mxi]>mx-i+1，答案一定是mx-i+1？
		next[i]=j;
		mx=i+j-1;
		mxi=i;
	}
	mx=0,mxi=1;
	for(int i=0;i<lens;i++) {
		if(next[i-mxi]<mx-i+1) {
			ans[i]=next[i-mxi];
			continue;
		}
		int j=max(0,mx-i+1);
		while(j<lenb&&i+j<lens&&B[j]==S[i+j]) j++;
		ans[i]=j;
		mx=i+j-1;
		mxi=i;
	}
}

int main()
{
	cin>>S>>B;
	extkmp(S,B,ans,next);
	int lens=strlen(S),lenb=strlen(B);
	for(int i=0;i<lenb;i++) cout<<next[i]<<" ";
	cout<<endl;
	for(int i=0;i<lens;i++) cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}