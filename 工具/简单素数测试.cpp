#include<bits/stdc++.h>

int main()
{
	long long a;
	while(scanf("%lld",&a)==1) {
		long long k=sqrt(a),i;
		for(i=2;i<=k;i++) {
			if(a%i==0) {
				puts("NO");
				break;
			}
		}
		if(i>k) puts("YES");
	}
	return 0;
}
