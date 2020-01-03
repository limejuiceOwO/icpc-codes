#include<cstdio>
using namespace std;

int fail[100001];
char str[1000002],pattern[10002];

int kmp()
{
  fail[0]=fail[1]=0;
  for(int i=1;pattern[i]!='\0';i++) {
    int f=fail[i];
    while(f&&pattern[i]!=pattern[f]) f=fail[f];
    fail[i+1]=(pattern[i]==pattern[f]?f+1:0);
  }
  int cnt=0;
  for(int i=0,j=0;str[i]!='\0';i++) {
    while(j&&str[i]!=pattern[j]) j=fail[j];
    if(str[i]==pattern[j]) j++;
    if(pattern[j]=='\0') cnt++;
  }
  return cnt;
}

signed main()
{
  int T;
  scanf("%d",&T);
  getchar();
  while(T--) {
    scanf("%s",pattern);
    scanf("%s",str);
    printf("%d\n",kmp());
  }
}
