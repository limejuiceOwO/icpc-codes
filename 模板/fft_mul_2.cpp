//O(nlgn) 高精度乘法 迭代FFT实现
#include <cstdio>
#include <algorithm>
#include <complex>
#define N 100005
#define NN 262149
using namespace std;
typedef complex<double> cp;

const double pi=3.14159265359;
cp w[NN],x[NN],y[NN];
int st[NN];

void getw(int n,bool rev)
{
	int s=rev?-1:1;
	for(int i=0;i<n;i++) {
		w[i]=cp(cos(2.0*s*pi*i/n),sin(2.0*s*pi*i/n));
	}
}

void rev_arr(unsigned int n,cp *arr)
{
	unsigned int j=0;
	for(unsigned int i=0;i<n;i++) {
		unsigned int mask=n>>1;
		if(i>j) swap(arr[i],arr[j]);
		while(j&mask) mask>>=1;
		j=((j|mask)&((mask<<1)-1));
	}
}

void itr_dft(int n,cp *vec)
{
	rev_arr(n,vec);

	for(int step=2;step<=n;step<<=1) {
		for(int base=0;base<n;base+=step) {
			for(int i=0;i<step/2;i++) {
				cp tmp=vec[base+i];
				vec[base+i]=tmp+w[n/step*i]*vec[base+i+step/2];
				vec[base+i+step/2]=tmp-w[n/step*i]*vec[base+i+step/2];
			}
		}
	}
}

int expand(int n)
{
	int r=1;
	while(r<n) r<<=1;
	return r;
}

void reverse(cp *p,int n)
{
	for(int i=0;i<n/2;i++) {
		swap(p[i],p[n-i-1]);
	}
}

int fft_mul(int n1,int n2,cp *x,cp *y)
{
	int n=expand(2*max(n1,n2));

	getw(n,false);
	itr_dft(n,x);
	itr_dft(n,y);

	for(int i=0;i<n;i++) x[i]*=y[i];

	getw(n,true);
	itr_dft(n,x);

	for(int i=0;i<n;i++) x[i]/=n;
	while(n&&fabs(x[n-1].real())<0.5) n--;

	return n;
}

int main()
{
	char ch;
	int n1=0,n2=0,n;

	while(isalnum(ch=getchar())) x[n1++]=cp(ch-'0',0);
	while(isalnum(ch=getchar())) y[n2++]=cp(ch-'0',0);

	reverse(x,n1);
	reverse(y,n2);

	n=fft_mul(n1,n2,x,y);

	if(n==0) {
		puts("0");
		return 0;
	}

	int top=0;
	int ovf=0;
	for(int i=0;i<n;i++) {
		int r=(int)(x[i].real()+0.5);
		st[top++]=(r+ovf)%10;
		ovf=(r+ovf)/10;
	}

	while(ovf) st[top++]=ovf%10,ovf/=10;

	while(top--) printf("%d",st[top]);

	putchar('\n');

	return 0;
}