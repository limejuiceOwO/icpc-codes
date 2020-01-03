#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 20005
using namespace std;
char buf[N],buf2[2*N];

void pre(const char *src,char *dst)
{
	while(*src!='\0') {
		if(isalpha(*(src++))) { 
			*(dst++)='$';*(dst++)=tolower(*(src-1)); 
		}
	}
	*dst='$';
}

int main()
{
	gets(buf);
	pre(buf,buf2);
	cout<<buf2<<endl;
	int len=strlen(str),mx=-1,ml=-1,mxi=-1;
	static int ans[1005];
	for(int i=0;i<len;i++) {
		int st=i+1;
		if(i<mx) st=min(mx,i+ans[(mxi<<1)-i]);
		while(st<len&&str[st]==str[(i<<1)-st]) st++;
		st=min(st,len);
		ml=max(ml,(ans[i]=st-i));
		if(st>mx) {
			mx=st;
			mxi=i;
		}
	}
	printf("%d\n",ml-1);
	return 0;
}