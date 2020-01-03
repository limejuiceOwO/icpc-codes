#include<iostream>
#include<algorithm>
using namespace std;
int V[100];
int W[100];
int d[1001];

int main()
{
    int C,n;
    cin >> n >> C;
    for(int i = 0;i<n;i++)
    	cin >> V[i] >> W[i];
    for(int i = n-1;i>=0;i--)
 	   for(int j=C;j>=0;j--) //d(i,j) = max(d(i+1,j),d(i+1,j-V[i])+1) d(n,0) = 0;
    		if(j>=V[i]) d[j] = max(d[j-V[i]] + W[i],d[j]);
    cout << d[C] << endl;
    return 0;
}
//01背包 递推 循环数组 
