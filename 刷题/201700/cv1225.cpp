#include<bits/stdc++.h>
using namespace std;
struct State {
	char board[9];
	int d,e;
	bool operator <(const State &rhs) const
	{
		return d+e>rhs.d+rhs.e;
		//return d>rhs.d;
	}
};
const char target[]={1,2,3,8,0,4,7,6,5};
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1},to[3][3]={{0,1,2},{3,4,5},{6,7,8}};

int estimate(char *board)
{
	int e=9;
	for(int i=0;i<9;i++)
		if(board[i]==target[i]) e--;
	return max(e-1,0);
}

int encode(char *board)
{
	int code=0;
	for(int i=0;i<9;i++)
		code=10*code+board[i];
	return code;
}

int search(State s)
{
	set<int> vis;
	priority_queue<State> pq;
	pq.push(s);
	vis.insert(encode(s.board));
	while(!pq.empty()) {
		State st;
		int x=-1,y=-1;
		st=pq.top();pq.pop();
		/*
		printf("%d %d\n",st.d,st.e);
		for(int i=0;i<9;i++)
			printf("%d",st.board[i]);
		puts("");
		*/
		if(st.e==0) return st.d;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(st.board[to[i][j]]==0) {
					x=i;y=j;break;
				}
		assert(x>=0&&y>=0);
		for(int i=0;i<4;i++) {
			int nx=x+dx[i],ny=y+dy[i];
			if(nx>=0&&ny>=0&&nx<3&&ny<3) {
				State nst;
				int e;
				memcpy(nst.board,st.board,9);
				nst.board[to[x][y]]=nst.board[to[nx][ny]];
				nst.board[to[nx][ny]]=0;
				if(vis.count(e=encode(nst.board))) continue;
				vis.insert(e);
				nst.d=st.d+1;
				nst.e=estimate(nst.board);
				pq.push(nst);
			}	
		}
	}
	return -1;
}

signed main()
{
	State s;
	for(int i=0;i<9;i++)
		s.board[i]=getchar()-'0';
	s.d=0;
	s.e=estimate(s.board);
	printf("%d\n",search(s));
}
