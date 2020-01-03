//搬雕像 排序+大量H2O
#include <iostream>
#include <algorithm>
struct A {
	int id,w,h;
	bool operator <(const A &rhs) const {
		return (h==rhs.h)?w<rhs.w:h<rhs.h;
	}
}arr[10005];

int main()
{
	int n,sum=0;
	std::cin>>n;
	for(int i=0;i<n;i++) {
		arr[i].id=i;
		std::cin>>arr[i].h>>arr[i].w;
	}
	std::stable_sort(arr,arr+n);
	for(int i=0;i<n;i++) {
		sum+=abs(arr[i].id-i);
	}
	std::cout<<sum<<"\n";
	return 0;
}