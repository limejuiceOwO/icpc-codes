//FFT 递归实现
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> cp;

const double pi=3.14159265359;

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