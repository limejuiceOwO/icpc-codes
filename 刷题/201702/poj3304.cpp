#include <iostream>
#define N 105
using namespace std;

const double EPS=1e-8;
struct Line {
	double x1,x2,y1,y2;
} lines[N];

bool check(int sx,int sy)
{
	int sx=x[i],sy=y[i];
	for(int i=0;i<n;j++) {
		double k1=(lines[i].y1-sy)/(lines[i].x1-sx),k2=(y[i]-
	}
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) cin>>lines[i].x1>>lines[i].x2>>lines[i].y1>>lines[i].y2;
	for(int i=0;i<n;i++) {
		
	}
}