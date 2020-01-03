#include<iostream>
using namespace std;

int kmp(const string &str,const string &pattern)
{
  int *fail=new int[pattern.length()+1];
  fail[0]=fail[1]=0;
  //pattern[length]='$';
  for(int i=1;i<pattern.length();i++) {
    int f=fail[i];
    while(f&&pattern[i]!=pattern[f]&&pattern[i+1]==pattern[f+1]) f=fail[f];
    fail[i+1]=(pattern[i]==pattern[f]?f+1:0);
  }
  int cnt=0;
  for(int i=0,j=0;i<str.length();i++) {
    while(j&&str[i]!=pattern[j]) j=fail[j];
    if(str[i]==pattern[j]) j++;
    if(j==pattern.length())  cnt++;
  }
  delete fail;
  return cnt;
}

signed main()
{
  int T;
  cin>>T;
  cin.get();
  while(T--) {
    string s,p;
    getline(cin,p);
    getline(cin,s);
    cout<<kmp(s,p)<<endl;
  }
}
