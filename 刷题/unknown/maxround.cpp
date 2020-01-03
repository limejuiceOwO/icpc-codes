#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

int dist[200000];
set<int> vis;

int main()
{
	int n,minround=999999;
	cin >> n;
	for(int i=0;i<n;i++)
		cin >> dist[i];
	for(int i=0;i<n;i++) {
		int j=i,round;
		if(!vis.count(j))
			round=0;
		while(!vis.count(j)) {
			vis.insert(j);
			j=dist[j]-1;
			round++;
		}
		minround = min(minround,round);
		//vis.clear();
	}
	cout << minround;
	return 0;
 } 
