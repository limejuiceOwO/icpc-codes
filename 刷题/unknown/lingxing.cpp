#include<cstdio>
#include<cmath>

int main()
{
	int r;
	scanf("%d",&r);
	for(int i=-r;i<=r;i++) {
		for(int j=-r;j<=r;j++)
			putchar(abs(i)+abs(j)==r?'*':' ');
		putchar('\n');
	}
	return 0;
}
