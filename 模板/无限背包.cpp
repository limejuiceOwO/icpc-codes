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
    for(int i = 0;i<=C;i++)
    	for(int j=0;j<n;j++)
    		if(i>=V[j]) d[i] = max(d[i-V[j]] + W[j],d[i]);
    cout << d[C] << endl;
    return 0;
}
//无限背包 递推 
