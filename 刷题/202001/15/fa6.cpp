#include <bits/stdc++.h>
using namespace std;

int bitarr[2005][2005];

struct Squ {
	double x1,x2,y1,y2;
} squ[1005];

double ptnx[2005],ptny[2005];

int main()
{
	ios::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		memset(bitarr,0,sizeof(bitarr));
		int px = 0,py = 0;
		for(int i = 0;i < n;i++) {
			cin >> squ[i].x1 >> squ[i].y1 >> squ[i].x2 >> squ[i].y2;
			ptnx[px++] = squ[i].x1;
			ptnx[px++] = squ[i].x2;
			ptny[py++] = squ[i].y1;
			ptny[py++] = squ[i].y2;
		}
		sort(ptnx,ptnx + px);
		px = unique(ptnx,ptnx + px) - ptnx;
		sort(ptny,ptny + py);
		py = unique(ptny,ptny + py) - ptny;

		for(int i = 0;i < n;i++) {
			int x1 = lower_bound(ptnx,ptnx + px,squ[i].x1) - ptnx;
			int x2 = lower_bound(ptnx,ptnx + px,squ[i].x2) - ptnx;
			int y1 = lower_bound(ptny,ptny + py,squ[i].y1) - ptny;
			int y2 = lower_bound(ptny,ptny + py,squ[i].y2) - ptny;

			bitarr[x2][y2]++;
			bitarr[x1][y2]--;
			bitarr[x2][y1]--;
			bitarr[x1][y1]++;
		}

		double ans = 0;
		for(int i = 0;i < px - 1;i++) {
			for(int j = 1;j < py - 1;j++) {
				bitarr[i][j] += bitarr[i][j - 1];
			}
		}
		for(int i = 0;i < px - 1;i++) {
			for(int j = 0;j < py - 1;j++) {
				int &v = bitarr[i][j];
				if(i > 0)
					v += bitarr[i - 1][j];
				//cout << v << endl;
				if(v > 1) {
					double x = ptnx[i + 1] - ptnx[i];
					double y = ptny[j + 1] - ptny[j];
					ans += x * y;
				}
			}
		}
		cout << fixed << setprecision(2) << ans + 0.000001 << endl;
	}
	return 0;
}