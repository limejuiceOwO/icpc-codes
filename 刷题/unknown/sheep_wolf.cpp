#include<iostream>
#include<cstdlib> 
#include<cmath>
#include<fstream>
using namespace std;

char board[100][250];
int sh,wo,R,S; 
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

void dfs(int x,int y)
{
     char c = board[x][y];
     if(c == 'o') sh++;
     else if(c == 'v') wo++;
     else if(c == '#') return;
     board[x][y] = '#';
     for(int i = 0;i < 4;i++) {
             int x2 = x + dx[i],y2 = y + dy[i];
             if(x2 >= 0&&x2 < R&&y2 >= 0&&y2 < S)
                   dfs(x2,y2);
     }
}

int main()
{
    int tsh = 0,two = 0;
    cin >> R >> S;
    for(int i = 0;i<R;i++)
            cin >> board[i];
    for(int i = 0;i < R;i++)
            for(int j = 0;j < S;j++)
                      if(board[i][j] != '#') {
                              dfs(i,j);
                              if(sh > wo) tsh += sh;
                              else two += wo;
                              sh = wo = 0;
                      }
    cout << tsh << " " << two << endl;
    system("pause");
    return 0; 
}
