#include<cstdio>
#include<stack>
using namespace std;

stack<char> num1,num2,res;

int main()
{
  char c;
  while((c=getchar())!=' ')
    num1.push(c-'0');
  while((c=getchar())!='\n')
    num2.push(c-'0');
  puts("fuck");
  int of=0;
  while(!(num1.empty()||num2.empty())) {
    int n1=num1.top(),n2=num2.top();
    num1.pop();num2.pop();
    res.push((n1*n2+of)%10);
    of=(n1*n2+of)/10;
  }
  if(!num1.empty()) {
    int n=num1.top();
    res.push((n+of)%10);
    num1.pop();
    of=(n+of)/10;
  }
  if(!num2.empty()) {
    int n=num2.top();
    res.push((n+of)%10);
    num2.pop();
    of=(n+of)/10;
  }
  while(!res.empty()) {
    putchar(res.top()+'0');
    res.pop();
  }
  puts("");
  return 0;
}
