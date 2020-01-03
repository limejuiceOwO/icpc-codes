#include<iostream>
#include<algorithm>
using namespace std;
int V[100];
int d[1001];

int main()
{
    int C,n;
    cin>>C>>n;
    for(int i = 0;i<n;i++)
    	cin >> V[i];
    for(int i=0;i<=C;i++)
    	d[i]=i;
    for(int j=0;j<n;j++)
    	for(int i = C;i>=0;i--) 
    		if(i>=V[j]) d[i] = min(d[i-V[j]],d[i]);
    cout << d[C] << endl;
    return 0;
}
