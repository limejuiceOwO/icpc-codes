#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
	int a,b,cnt=0;
	cin>>a>>b;
	if(b%a) {
		cout<<'0'<<endl;
		return 0;
	}
	int c=b/a;
	for(int i=2;i<=sqrt(c+0.5);i++)
		if(c%i==0) {
			cnt++;
			while(c%i==0) c/=i;
		}
	if(c!=1) cnt++;
	cout<<pow(2,cnt)<<endl;
	return 0; 
}
