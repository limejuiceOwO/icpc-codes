//An Easy Problem?
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;
const double EPS=1e-8;

struct Vec {
	double x,y;
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator +(const Vec &rhs) {
		return Vec(x+rhs.x,y+rhs.y);
	}
	Vec operator -(const Vec &rhs) {
		return Vec(x-rhs.x,y-rhs.y);
	}
	Vec operator *(double v) {
		return Vec(x*v,y*v);
	}
	double det(const Vec &rhs) {
		return x*rhs.y-y*rhs.x;
	}
	double ang() {
		return atan2(y,x); //[-PI,PI]
	}
	bool parallel(const Vec &rhs) {
		return fabs(det(rhs))<EPS;
	}
	friend std::istream& operator >>(std::istream &in,Vec &v);
};

bool intersection(Vec &ans,Vec p1,Vec p2,Vec p3,Vec p4) //two segments on the same line?
{
	Vec l1=p3-p1,l2=p4-p1,l3=p3-p2,l4=p4-p2;
	double d1=l1.det(l2),d2=l4.det(l3);
	if(d1*d2<0||l1.det(l3)*l2.det(l4)>0) return false; //four dets,make sure any two points are on different sides
	ans=p1+(p2-p1)*fabs(d1/(d1+d2));
	return true;
}

std::istream& operator >>(std::istream &in,Vec &v)
{
	return in>>v.x>>v.y;
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--) {
		Vec a,b,c,d,p;
		cin>>a>>b>>c>>d;
		if((a-b).parallel(c-d)||!intersection(p,a,b,c,d)) { //not parallel && intersect
			cout<<"0.00"<<endl;
			continue;
		}
		Vec ma=a.y>b.y?a:b,mb=c.y>d.y?c:d;
		if(ma.y>mb.y) swap(ma,mb);
		Vec l1=ma-p,l2=mb-p;
		Vec tl1=l1,tl2=l2;
		if(l1.ang()>l2.ang()) swap(tl1,tl2);
		if(((tl1.x*tl2.x>0)&&(tl1.x-tl2.x<EPS))||fabs(l1.y)<EPS) { //uncovered && height!=0
			cout<<"0.00"<<endl;
			continue;
		}
		cout<<fixed<<setprecision(2)<<(fabs(l1.x-l2.x*(l1.y/l2.y)))*(l1.y)/2<<endl;//l2.y!=0
	}
	return 0;
}