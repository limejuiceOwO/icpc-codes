#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int p[129][129];

int c(int x,int y,int d)
{
	int n = 0;
	for(int i = max(x - d,0);i <= min(x + d,128);i++)
		for(int j = max(y - d,0);j <= min(y + d,128);j++)
			n += p[i][j];
	return n;
}


int main()
{
	int d,n;
	int maxn = -1,maxc = 0;
	//freopen("wireless.in","r",stdin);
	//freopen("wireless.out","w",stdout);
	cin >> d >> n;
	for(int i = 0;i<n;i++) {
		int x,y;
		cin >> x >> y;
		cin >> p[x][y];
	}
	for(int x = 0;x < 129;x++)
		for(int y = 0;y < 129;y++) {
			int n = c(x,y,d);
			//printf("%d %d %d\n",x,y,n);
			if(maxn == n) {
				maxc++;
			} else if(maxn < n) {
				maxn = n;
				maxc = 1;
			}
		}
	cout << maxc << ' ' << maxn << endl;
	return 0;
}
/*
NOIP2015 day1
*/ 
