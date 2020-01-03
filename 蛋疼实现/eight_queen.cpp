#include<iostream>
using namespace std;

int board[8];
int count;

bool valid(int line,int col)
{
  for(int i=0;i<line;i++)
    if(board[i] == col||board[i] + line - i == col||board[i] - line + i == col)
      return false;
  return true;
}

void print()
{
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++)
      if(board[i] == j) 
        cout << "#";
      else
        cout << ".";
  cout << endl;
  }
  cout << endl;
  count++;
}

void solve(int line)
{
  for(int i=0;i<8;i++) {
    if(valid(line,i)) {
      board[line]=i;
      if(line == 7)
        print();
      else
        solve(line + 1);
    }
  }
}

int main()
{
  solve(0);
  cout << count << endl;
  return 0;
}
