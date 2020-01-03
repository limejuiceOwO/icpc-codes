#include <iostream>
#include <algorithm>
#define N 25
using namespace std;

struct Point {
	double x,y;
} cent[N];
double r[N];

int main()
{
	while(1) {
		int n;
		cin>>n;
		if(n==0) break;
		for(int i=0;i<n;i++) {
			cin>>cent[i].x>>cent[i].y>>r[i];
		}
		double x,y,dx,dy;
		cin>>x>>y>>dx>>dy;
		for(int cnt=0;cnt<20;cnt++) {
			for(int i=0;i<n;i++) {
				double d=det(dx,dy,x-cent[i].x,y-cent[i].y)/sqrt(dx*dx+dy*dy);
				if(d<r[i]) {
					
				}
			}
		}
	}
}