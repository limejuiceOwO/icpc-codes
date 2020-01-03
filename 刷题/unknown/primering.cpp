#include<iostream>
#include<cstring>
using namespace std;
int ans[100]; 
int v[100]; 
int prime[100];
int n;

void gen()
{
	memset(prime,1,sizeof(prime));
	for(int i=2;i<100;i++)
		if(prime[i])
			for(int j=i*i;j<100;j+=i)
				prime[j]=0;		
}

void solve(int d) 
 {
 	if(d>=n)
 		if(prime[ans[n-1]+ans[0]]) {
 			for(int i = 0;i<n;i++)
 				cout << ans[i] << ' ';
	 		cout << endl;
	 		return;
	 	} else return; 
 	for(int i = 2;i <= n;i++)
	 	if(!v[i]&&prime[i+ans[d-1]]) {
	 		ans[d] = i;
	 		v[i]=1;
	 		solve(d+1);
	 		v[i]=0;
		 }
 }
 
int main()
{
	cin>>n;
	gen();
 	ans[0]=1;
 	v[1]=1;
 	solve(1);
	return 0; 
} 
