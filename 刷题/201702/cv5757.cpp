#include <cstdio>
#include <cstring>
#define N 505
#define M 1000005
using namespace std;

int fail[N];
char str[M],pattern[N];

int main()
{
  freopen("kmp.in","r",stdin);
  scanf("%s%s",pattern,str);
  int cnt=0;
  fail[0]=fail[1]=0;
  for(int i=1;pattern[i]!='\0';i++) {
    int f=fail[i];
    while(f&&pattern[i]!=pattern[f]) f=fail[f];
    fail[i+1]=(pattern[i]==pattern[f]?f+1:0);
  }
  for(int i=0,j=0;str[i]!='\0';i++) {
    while(j&&str[i]!=pattern[j]) j=fail[j];
    if(str[i]==pattern[j]) j++;
    if(pattern[j]=='\0') cnt++;
  }
  printf("%d\n",cnt);
  return 0;
}
