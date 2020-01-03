#include <cmath>
#include <iostream>
using namespace std;

const double EPS=1e-8;
const double PI=3.1415926535898;

inline int fil(double x)
{
	return x>EPS?1:(x<-EPS?-1:0);
}

struct Vec {
	double x,y;
	
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator -() {
		return Vec(-x,-y);
	}
	Vec operator +(const Vec &rhs) {
		return Vec(x+rhs.x,y+rhs.y);
	}
	Vec operator -(const Vec &rhs) {
		return Vec(x-rhs.x,y-rhs.y);
	}
	Vec operator *(double v) {
		return Vec(x*v,y*v);
	}
	Vec operator /(double v) {
		return Vec(x/v,y/v);
	}
	bool operator ==(const Vec &rhs) {
		return fil(x-rhs.x)<0&&fil(y-rhs.y)<0;
	}
	double d() {
		return sqrt(x*x+y*y);
	}
	double rad() {
		return atan2(y,x);
	}
	Vec i() {
		const double len=d();
		return fil(len)==0?Vec(0,0):Vec(x/len,y/len);
	}
	Vec spin(double theta) {
		const double rsin=sin(theta),rcos=cos(theta);
		return Vec(x*rcos-y*rsin,x*rsin+y*rcos);
	}
	double dot(const Vec &rhs) {
		return x*rhs.x+y*rhs.y;
	}
	double det(const Vec &rhs) {
		return x*rhs.y-y*rhs.x;
	}
	bool on(Vec p1,Vec p2) {
		return max(p1.x,p2.x)-x>-EPS
		     &&x-min(p1.x,p2.x)>-EPS
		     &&max(p1.y,p2.y)-y>-EPS
		     &&y-min(p1.y,p2.y)>-EPS;
	}
	bool parallel(const Vec &rhs) {
		return fil(det(rhs))==0;
	}
	friend std::istream& operator >>(std::istream &in,Vec &v);
	friend std::ostream& operator <<(std::ostream &in,const Vec &v);
};

bool intersection(Vec &ans,Vec p1,Vec p2,Vec p3,Vec p4)
{
	Vec l1=p3-p1,l2=p4-p1,l3=p3-p2,l4=p4-p2,l5=p2-p1,l6=p3-p4;
	double d1=l1.det(l2),d2=l4.det(l3);
	if(fabs(l6.det(l3))<EPS&&fabs(l6.det(l1))<EPS) return p1.on(p3,p4)||p2.on(p3,p4)||p3.on(p1,p2)||p4.on(p1,p2);
	if(l5.det(l1)*l5.det(l2)>0||l6.det(l1)*l6.det(l3)>0) return false;
	ans=p1+(p2-p1)*fabs(d1/(d1+d2));
	return true;
}

std::istream& operator >>(std::istream &in,Vec &v)
{
	return in>>v.x>>v.y;
}

std::ostream& operator <<(std::ostream &out,const Vec &v)
{
	return out<<"("<<v.x<<","<<v.y<<")";
}