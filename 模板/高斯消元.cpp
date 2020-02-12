#include <algorithm>
#include <cmath>
#define EPS 1e-6

double A[N][N],B[N];
int primary[N];

void swapline(int i,int j)
{
	if(i != j) {
		swap(A[i],A[j]);
		swap(B[i],B[j]);
	}
}

void subline(int n,int i,int j,int prim)
{
	double m = A[i][prim];
	for(int k = prim;k < n;k++) {
		A[i][k] -= A[j][k] * m;
	}
	B[i] -= B[j] * m;
}

void gauss(int n)
{
	int ln = 0;
	for(int prim = 0;prim < n;prim++) {
		for(int i = ln;i < n;i++) {
			if(fabs(A[i][prim]) > EPS) {
				swapline(ln,i);
				goto found;
			}
		}
		continue;
		found:
		double m = A[ln][prim];
		for(int i = 0;i < n;i++)
			A[ln][i] /= m;
		B[ln] /= m;
		for(int i = ln + 1;i < n;i++) {
			if(fabs(A[i][prim]) > EPS)
				subline(n,i,ln,prim);
		}
		primary[ln++] = prim;
	}
	for(int i = ln;i < n;i++)
		primary[i] = -1;
	while((ln--) > 1) {
		int prim = primary[ln];
		for(int i = 0;i < ln;i++) {
			if(fabs(A[i][prim]) > EPS)
				subline(n,i,ln,prim);
		}
	}
}

int main()
{
	//matrix input
	gauss(n);
	//...
}
