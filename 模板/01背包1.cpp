#include<iostream>
#include<algorithm>
using namespace std;
int V[100];
int W[100];
int d[101][1000];

int main()
{
    int C,n;
    cin >> C >> n;
    for(int i = 0;i<n;i++)
    	cin >> V[i] >> W[i];
	//memset(d[0],0,sizeof(d[0]));
    for(int i = 1;i<=n;i++)
 	   for(int j=C;j>=0;j--) { //d(i,j) = max(d(i+1,j),d(i+1,j-V[i])+1) d(n,0) = 0;
    		d[i][j] = d[i-1][j];
    		if(j>=V[i-1]) d[i][j] = max(d[i-1][j-V[i-1]] + W[i-1],d[i][j]);
		}
    cout << d[n][C] << endl;
    
    int p=C;
    for(int i=n-1;i>=0;i--)
    	if(p>=V[i]&&d[i+1][p]==d[i][p-V[i]]+W[i]) { //d[i][p]<d[i][p-V[i]]+W[i]
    		cout<<i<<endl;
    		p-=V[i];
		}
	cout<<endl<<p<<endl;
	
    return 0;
}
//01±³°ü µÝÍÆ 
