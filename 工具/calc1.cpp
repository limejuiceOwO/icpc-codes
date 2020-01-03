#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

char ops[]="+-*/()";
stack<double> num;
stack<char> op;
int p;

void error()
{
	cout<<"Wrong expression."<<endl;
	exit(1);
}

int priority(char opr)
{
	switch(opr) {
		case '$':
			return 0;
		case '*':
		case '/':
			return 1;
		case '+':
		case '-':
			return 2;
		case '(':
			return 3;
		default:
			error();
	}
}

double eval(double x1,double x2,int opr)
{
	if(opr=='+') return x1+x2;
	if(opr=='-') return x1-x2;
	if(opr=='*') return x1*x2;
	if(opr=='/') return x1/x2;
	else error();
}

void process()
{
	char opr=op.top();
	op.pop();
	if(opr==')') {
		opr=op.top();op.pop();
		while(opr!='(') {
			double x1=num.pop();
			double x2=num.pop();
			num.push(eval(x1,x2,opr));
			opr=op.top();op.pop();
		}
		return;
	}
	for(char opr2=op.top();priority(opr)>priority(opr2);opr2=op.top()) {
		double x1=num.pop();
		double x2=num.pop();
		num.push(eval(x1,x2,opr));
		op.pop();
		opr=opr2;
	}
	op.push(opr);
}

inline bool isnum(char c)
{
	return c>='0'&&c<='9';
}

inline bool isopr(char c)
{
	for(int i=0;i<sizeof(ops);i++) {
		if(c==ops[i]) return true;
	}
	return false;
}

double getnum()
{
	//int s=1;
	double x=0;
	//if(expr[p]=='-') s=-1,p++; 
	while(isnum(expr[p])) x=x*10+expr[p++]-'0';
	if(expr[p]=='.') {
		int prev=p++;
		while(isnum(expr[p])) x=x*10+expr[p++]-'0';
		x/=10*(p-prev);
	}
	return x;
}

int main()
{
	string expr;
	getline(cin,expr);
	expr+='$';
	while(expr[p])　{
		if(isnum(expr[p])) {
			double x=getnum();
			num.push(x);
			process();
		} else if(isopr(expr[p])) {
			char o=expr[p++];
			op.push(o);
			process();
		} else {
			error();
		}
	}
	cout<<num.top()<<endl;
	return 0;
}