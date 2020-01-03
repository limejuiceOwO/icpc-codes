#include<iostream>
using namespace std;
typedef long long LL;
char exp[100];
char* cur;

int err = 0;

LL nextsym(int& type)
{
  while(isspace(*cur)) cur++;
  if(*cur=='+'|*cur=='-'|*cur=='*'|*cur=='/') {
    type = 2;
    return *(cur++);
  } else if(isdigit(*cur)) {
    LL num = 0;
    while(isdigit(*cur)) {
     num += *cur - '0';
     num *= 10;
     cur++;
    }
    type = 1;
    return num;
  } else {
    type = 0;
    return 0;
  }
}

LL opr(LL op,LL a,LL b)
{
  switch(op) {
    case '+':return a+b;
    case '-':return a-b;
    case '*':return a*b;
    case '/':return a/b;
  }
}

LL rev_polland()
{
  int type;
  if(err) return 0;
  LL sym = nextsym(type);
  if(type == 1)
    return sym;
  else if(type == 2){
    LL a = rev_polland();
    LL b = rev_polland();
    if(err) return 0;
    return opr(sym,a,b);
  } else {
    err = 1;
    return 0;
  }
}

int main()
{
  cin >> exp;
  while(exp[0] != 'q') {
    cur = exp;
    err = 0;
    LL ans = rev_polland();
    if(err) cout << "Wrong expression.\n";
    else cout << ans << endl;
    cin >> exp;
  }
  return 0;
}
