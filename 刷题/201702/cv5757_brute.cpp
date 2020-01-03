#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 505
#define M 1000005
using namespace std;

char str[M],pattern[N];

int main()
{
	//freopen("kmp.in","r",stdin);
	scanf("%s%s",pattern,str);
	int l1=strlen(pattern),l2=strlen(str);
	int cnt=0;
	for(int i=0;i<l2-l1+1;i++) {
		int j;
		for(j=0;j<l1&&str[i+j]==pattern[j];j++);
		if(j==l1) cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}