#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int C,n;
int V[100];
int W[100];
int d[101][1000];
int cnt;

int bag(int i,int v)
{
	if(v<0) return -1;
	if(i==n||v==0) return 0;
	if(d[i][v]>=0) return d[i][v];
	cnt++;
	return d[i][v] = max(bag(i+1,v),bag(i+1,v-V[i])+W[i]);
}

int main()
{
    cin >> C >> n;
    for(int i = 0;i<n;i++)
    	cin >> V[i] >> W[i];
    memset(d,-1,sizeof(d));
    cout << bag(0,C) <<endl;
    cout<<cnt<<endl;
    return 0;
}
//01±³°ü ¼ÇÒä»¯ËÑË÷ 
