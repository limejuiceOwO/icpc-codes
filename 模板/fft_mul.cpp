//O(nlgn) 高精度乘法 递归FFT实现
#include <cstdio>
#include <algorithm>
#include <complex>
#define N 100005
#define NN 262149
using namespace std;
typedef complex<double> cp;

const double pi=3.14159265359;
cp w[NN],x[NN],y[NN],tmp[NN],ret[NN];
long long st[NN];

void getw(int n,bool rev)
{
	int s=rev?-1:1;
	for(int i=0;i<n;i++) {
		w[i]=cp(cos(2.0*s*pi*i/n),sin(2.0*s*pi*i/n));
	}
}

void rec_dft(int n,const cp *vec,cp *ret,int base=0,int step=1,int rbase=0)
{
	if(n==1) {
		ret[rbase]=vec[base];
		return;
	}

	rec_dft(n>>1,vec,ret,base,step<<1,rbase);
	rec_dft(n>>1,vec,ret,base+step,step<<1,rbase+n/2);

	for(int i=0;i<n/2;i++) {
		int u=rbase+i,v=rbase+i+n/2;
		cp tmp=ret[u];
		ret[u]=tmp+w[i*step]*ret[v];
		ret[v]=tmp-w[i*step]*ret[v];
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

int fft_mul(int n1,int n2,cp *x,cp *y,cp *ret,cp *tmp)
{
	int n=expand(2*max(n1,n2));

	getw(n,false);
	rec_dft(n,x,ret);
	rec_dft(n,y,tmp);

	for(int i=0;i<n;i++) tmp[i]*=ret[i];

	getw(n,true);
	rec_dft(n,tmp,ret);

	for(int i=0;i<n;i++) ret[i]/=n;
	while(n&&fabs(ret[n-1].real())<0.5) n--;

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

	n=fft_mul(n1,n2,x,y,ret,tmp);

	if(n==0) {
		puts("0");
		return 0;
	}

	int top=0;
	long long ovf=0;
	for(int i=0;i<n;i++) {
		long long r=(long long)(ret[i].real()+0.5);
		st[top++]=(r+ovf)%10;
		ovf=(r+ovf)/10;
	}

	while(ovf) st[top++]=ovf%10,ovf/=10;

	while(top--) printf("%lld",st[top]);

	putchar('\n');

	return 0;
}