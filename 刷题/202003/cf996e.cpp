#include <iostream>
#include <cassert>
#define N 100005
#define LIMIT 1000000000000LL
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define sgn(x) ((x) >= 0 ? 1 : -1)
using namespace std;

long long vx[N],vy[N];
int sig[N];
struct Vec {
	int vlist[N];
	int n;
	long long x,y;
} v1,v2;

long long l2(long long x,long long y)
{
	return x * x + y * y;
}

int main()
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for(int i = 0;i < n;i++) 
		cin >> vx[i] >> vy[i];

	v1.n = v2.n = 1;
	v1.vlist[0] = 0;
	v2.vlist[0] = 1;
	v1.x = vx[0]; v1.y = vy[0];
	v2.x = vx[1]; v2.y = vy[1];
	for(int i = 2;i < n;i++) {
		int x = vx[i],y = vy[i];
		if(l2(v1.x + x,v1.y + y) <= LIMIT) {
			v1.vlist[v1.n++] = i;
			v1.x += x; v1.y += y;
		} else if(l2(v1.x - x,v1.y - y) <= LIMIT) {
			v1.vlist[v1.n++] = -i;
			v1.x -= x; v1.y -= y;
		} else if(l2(v2.x + x,v2.y + y) <= LIMIT) {
			v2.vlist[v2.n++] = i;
			v2.x += x; v2.y += y;
		} else if(l2(v2.x - x,v2.y - y) <= LIMIT) {
			v2.vlist[v2.n++] = -i;
			v2.x -= x; v2.y -= y;
		} else if(l2(v1.x + v2.x,v1.y + v2.y) <= LIMIT) {
			for(int i = 0;i < v2.n;i++) {
				v1.vlist[v1.n++] = v2.vlist[i];
			}
			v2.n = 1;
			v2.vlist[0] = i;
			v1.x += v2.x; v1.y += v2.y;
			v2.x = vx[i]; v2.y = vy[i];
		} else if(l2(v1.x - v2.x,v1.y - v2.y) <= LIMIT) {
			for(int i = 0;i < v2.n;i++) {
				v1.vlist[v1.n++] = -v2.vlist[i];
			}
			v2.n = 1;
			v2.vlist[0] = i;
			v1.x -= v2.x; v1.y -= v2.y;
			v2.x = vx[i]; v2.y = vy[i];
		} else {
			assert(false);
		}
	}

	if(l2(v1.x + v2.x,v1.y + v2.y) <= 2.25 * LIMIT) {
		for(int i = 0;i < v2.n;i++) {
			v1.vlist[v1.n++] = v2.vlist[i];
		}
	} else if(l2(v1.x - v2.x,v1.y - v2.y) <= 2.25 * LIMIT) {
		for(int i = 0;i < v2.n;i++) {
			v1.vlist[v1.n++] = -v2.vlist[i];
		}
	} else {
		assert(false);
	}

	sig[0] = 1;
	for(int i = 1;i < v1.n;i++)
		sig[abs(v1.vlist[i])] = sgn(v1.vlist[i]);
	
	for(int i = 0;i < n;i++) {
		cout << sig[i] << " ";
	}
	cout << endl;

	return 0;
}