#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
char buf[1005],buf2[2011];

void pre(const char *src,char *dst)
{
	while(*src!='\0') { *(dst++)='$';*(dst++)=*(src++); }
	*dst='$';
}

int manacher(const char *str)
{
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
	return ml-1;
}

int main()
{
	cin>>buf;
	pre(buf,buf2);
	cout<<manacher(buf2)<<endl;
	return 0;
}