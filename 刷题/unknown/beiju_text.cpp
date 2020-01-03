#include<iostream>
#include<cstring>
#include<deque>
using namespace std;
char text[1000];

int main()
{
  cin >> text;
  int len = strlen(text);
  deque<int> s;
  s.push_back(0);
  for(int i = 0;i < len;i++)
    if(text[i] == '[')
      s.push_front(i + 1);
    else if(text[i] == ']')
      s.push_back(i + 1);
  while(!s.empty()) {
    int i = s.front();
    s.pop_front();
    for(;i<len&&text[i]!=']'&&text[i]!='[';i++)
      cout << text[i];
  }
  return 0;
}
