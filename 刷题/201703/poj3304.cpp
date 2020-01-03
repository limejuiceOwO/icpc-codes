//Segments
#include <iostream>
#include <cmath>
#define N 105
using namespace std;

const double EPS=1e-8;
struct Vec {
	double x,y;
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator -(const Vec &rhs) {
		return Vec(x-rhs.x,y-rhs.y);
	}
	double det(const Vec &rhs) {
		return x*rhs.y-y*rhs.x;
	}
	friend std::istream& operator >>(std::istream &in,Vec &v);
} points[2*N],end1[N],end2[N];

std::istream& operator >>(std::istream &in,Vec &v)
{
	return in>>v.x>>v.y;
}

int fil(double x)
{
	return x>EPS?1:(x<-EPS?-1:0);
}

int main()
{
	ios::sync_with_stdio(false);
	int T,n;
	cin>>T;
	while(T--) {
		cin>>n;
		for(int i=0;i<n;i++) {
			cin>>end1[i]>>end2[i];
			points[i<<1]=end1[i];
			points[i<<1|1]=end2[i];
		}
		bool ok=false;
		for(int i=0;!ok&&i<(n<<1);i++) {
			for(int j=i+1;!ok&&j<(n<<1);j++) {
				int k;
				Vec line=points[i]-points[j];
				if(fabs(line.x)<EPS&&fabs(line.y)<EPS) break; //注意特判两点相等，此时det恒等于0
				for(k=0;k<n;k++) {
					if(fil(line.det(points[i]-end1[k]))*fil(line.det(points[i]-end2[k]))>0) break;
				}
				if(k==n) ok=true;
			}
		}
		if(ok) cout<<"Yes!"<<endl;
		else cout<<"No!"<<endl;
	}
	return 0;
}