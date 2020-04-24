//基于单调栈算法的多功能中缀表达式解析器
//by limejuice@HEBUT
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <iomanip>
#include <stack>
#include <map>
#include <exception>
using namespace std;

struct Node {
	string name;
	Node *ch[2];
};

struct ParseException : public exception {
	int position;
	ParseException(int pos):position(pos) {};
	string what() {
		return string("Syntax error at position ").append(to_string(position));
	}
};

Node *root;
map<string,bool> valuetable;
map<char,int> priority,ary;
stack<Node*> stk; //栈内所有元素的左操作数均确定，右操作数均不确定，优先级递增

void setary() //自定义运算符元数
{
	ary['!'] = 1;
	ary['&'] = ary['|'] = ary['>'] = ary['='] = 2;
}

void setpriority() //自定义运算符优先级
{
	priority['>'] = priority['='] = 0;
	priority['|'] = 1;
	priority['&'] = 2;
	priority['!'] = 3;
}

string trim(const string &s)
{
	string res;
	for(unsigned int i = 0;i < s.length();++i) {
		if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\v') {
			res.push_back(s[i]);
		}
	}
	return res;
}

string parsename(const string &expr,unsigned int pos)
{
	string res;
	while(pos < expr.length() && isalnum(expr[pos])) {
		res.push_back(expr[pos++]);
	}
	return res;
}

void parse(const string &expr) //将表达式转化为树形结构
{
	unsigned int pos = 0;
	Node *freetop = 0; //位于虚拟栈顶的右侧未绑定元素
	while(pos < expr.length()) {
		if(isalpha(expr[pos])) {
			if(freetop) {
				throw ParseException(pos);
			}
			string varname = parsename(expr,pos);
			freetop = new Node();
			freetop->name = varname;
			freetop->ch[0] = freetop->ch[1] = 0;
			if(!valuetable.count(varname)) {
				valuetable[varname] = false;
			}
			pos += varname.length();
		} else {
			char type = expr[pos];
			if(type == '(') {
				Node *newop = new Node();
				newop->name = string(1,type);
				newop->ch[0] = newop->ch[1] = 0;
				stk.push(newop);
			} else if(type == ')') {
				if(!freetop) {
					throw ParseException(pos);
				}
				while(!stk.empty() && stk.top()->name[0] != '(') {
					Node *rr = stk.top(); stk.pop();
					rr->ch[1] = freetop;
					freetop = rr;
				}
				if(stk.empty()) {
					throw ParseException(pos);
				}
				stk.pop();
			} else {
				if(!ary.count(type))
					throw ParseException(pos);
				if(ary[type] == 1) {
					if(freetop) {
						throw ParseException(pos);
					}
					Node *newop = new Node();
					newop->name = string(1,type);
					newop->ch[0] = 0;
					stk.push(newop);
				} else if(ary[type] == 2) {
					if(!freetop) {
						throw ParseException(pos);
					}
					int prior = priority[type];
					while(!stk.empty() && stk.top()->name[0] != '(' && priority[stk.top()->name[0]] >= prior) {
						Node *rr = stk.top(); stk.pop();
						rr->ch[1] = freetop;
						freetop = rr;
					}
					Node *newop = new Node();
					newop->name = string(1,type);
					newop->ch[0] = freetop;
					freetop = 0;
					stk.push(newop);
				} else {
					throw ParseException(pos);
				}
			}
			++pos;
		}
	}
	if(!freetop) {
		throw ParseException(pos);
	}
	while(!stk.empty()) {
		Node *rr = stk.top(); stk.pop();
		if(rr->name[0] == '(') {
			throw ParseException(pos);
		}
		rr->ch[1] = freetop;
		freetop = rr;
	}
	root = freetop;
}

bool eval(Node *p) //对树形结构求值
{
	if(isalnum(p->name[0])) {
		return valuetable[p->name];
	}

	switch(p->name[0]) { //自定义求值方式
		case '!':
			return !eval(p->ch[1]);
		case '&':
			return eval(p->ch[0]) && eval(p->ch[1]);
		case '|':
			return eval(p->ch[0]) || eval(p->ch[1]);
		case '>':
			return !eval(p->ch[0]) || eval(p->ch[1]);
		case '=':
			return !(eval(p->ch[0]) ^ eval(p->ch[1]));
	}
	assert(false);
	return false;
}

void print(Node *p)
{
	cout << "(";
	if(p->ch[0])
		print(p->ch[0]);
	cout << p->name;
	if(p->ch[1])
		print(p->ch[1]);
	cout << ")";
}

void destroy(Node *p)
{
	if(p->ch[0])
		destroy(p->ch[0]);
	if(p->ch[1])
		destroy(p->ch[1]);
	delete p;
}

int main()
{
	setary();
	setpriority();

	while(true) {
		if(root) {
			destroy(root);
			root = 0;
		}
		valuetable.clear();
		while(!stk.empty())
			stk.pop();

		cout << ">> ";
		string input; getline(cin,input);
		if(cin.eof())
			break;
		input = trim(input);
		
		try {
			parse(input);
		} catch(ParseException &e) {
			cout << e.what() << endl;
			continue;
		}

		print(root);
		cout << endl;
		//continue;

		for(map<string,bool>::iterator it = valuetable.begin();it != valuetable.end();++it) {
			cout << setw(5) << it->first;
		}
		cout << setw(5) << "RES" << endl;
		for(int bit = 0;bit < (1 << valuetable.size());++bit) {
			int i = 0;
			for(map<string,bool>::iterator it = valuetable.begin();it != valuetable.end();++it) {
				it->second = bit & (1 << i);
				cout << setw(5) << it->second;
				++i;
			}
			cout << setw(5) << eval(root) << endl;
		}
	}
	return 0;
}