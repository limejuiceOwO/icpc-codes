#include<iostream>
using namespace std;

int extgcd(int a,int b,int &x,int &y)
{
  if(b==0) {
    x=1;
    y=0;
    return a;
  } else {
    int g=extgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return g; //x=y',y=x'-(a/b)*y'
  }
}

int main()
{
  int a,b,x,y;
  cin>>a>>b;
  int e=extgcd(a,b,x,y);
  cout<<a<<"*"<<x<<"+"<<b<<"*"<<y<<"="<<e<<" \n";
  return 0;
}
//orz
