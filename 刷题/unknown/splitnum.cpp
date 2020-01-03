#include<iostream>
#include<algorithm>
using namespace std;

int ans[100];

void splitit(int n,int ma,int d)
{
	if(n==0) {
		for(int i=0;i<d;i++)
			cout << ans[i] << " ";
		cout << endl;
		return;
	}
	for(int i = ma;i<=n;i++) {
		ans[d] = i;
		splitit(n-i,i,d+1);
	}
}

int main()
{
	int n;
	cin >> n; //n <= 100
	splitit(n,1,0);
	return 0;
}
