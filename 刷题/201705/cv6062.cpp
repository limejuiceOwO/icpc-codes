#include <iostream>
#include <algorithm>
#define N 100005
using namespace std;

int arr[N],tot[3],cnt[3];

bool legal()
{
	for(int i=0;i<3;i++) {
		if(cnt[i]!=tot[i]/2) return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>arr[i];
		tot[arr[i]]++;
	}
	for(int i=0;i<n/2;i++) {
		cnt[arr[i]]++;
	}
	if(legal()) {
		cout<<"1"<<endl;
		return 0;
	}
	for(int i=n/2;i<n;i++) {
		cnt[arr[i-n/2]]--;
		cnt[arr[i]]++;
		if(legal()) {
			cout<<"2"<<endl;
			return 0;
		}
	}
	cout<<"3"<<endl;
	return 0;
}