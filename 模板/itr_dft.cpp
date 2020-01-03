//FFT 迭代实现
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> cp;

const double pi=3.14159265359;

void getw(int n,bool rev) //预处理出n次单位根
{
	int s=rev?-1:1;
	for(int i=0;i<n;i++) {
		w[i]=cp(cos(2.0*s*pi*i/n),sin(2.0*s*pi*i/n));
	}
}

void rev_arr(unsigned int n,cp *arr) //将数组下标二进制反转
{
	unsigned int j=0;
	for(unsigned int i=0;i<n;i++) {
		unsigned int mask=n>>1;
		if(i>j) swap(arr[i],arr[j]);
		while(j&mask) mask>>=1;
		j=((j|mask)&((mask<<1)-1));
	}
}

/*
void rev_arr_dalao(unsigned int n,cp *arr)
{
	for(unsigned int i=0,j=0;i<n;i++) {
		if(i>j) swap(arr[i],arr[j]);
		for(unsigned int l=n>>1;(j^=l)<l;l>>=1);
	}
}
*/

void itr_dft(int n,cp *vec)
{
	rev_arr(n,vec);

	for(int step=2;step<=n;step<<=1) { //注意step=n时还需要进行一次整体操作……
		for(int base=0;base<n;base+=step) {
			for(int i=0;i<step/2;i++) {
				cp tmp=vec[base+i];
				vec[base+i]=tmp+w[n/step*i]*vec[base+i+step/2];
				vec[base+i+step/2]=tmp-w[n/step*i]*vec[base+i+step/2];
			}
		}
	}
}