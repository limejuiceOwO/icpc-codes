#include<iostream>
using namespace std;
int main()
{
	int K,day=1;
	long long coins=0;
	cin >> K;
	while(K>0) {
		K -= day;
		coins += day*day;
		day++;
	}
	coins -= -K*(day-1);
	cout << coins;
	return 0;
}
