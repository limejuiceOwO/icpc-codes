//Dropping Tests
#include <iostream>
#include <algorithm>
#define N 1005
using namespace std;

int A[N],B[N];
double res[N];
const double EPS=1e-8;

int main()
{
    ios::sync_with_stdio(false);
    while(1) {
        int n,k;
        cin>>n>>k;
        if(n==0) break;
        for(int i=0;i<n;i++) {
            cin>>A[i];
        }
        for(int i=0;i<n;i++) {
            cin>>B[i];
        }
        double l=0,r=100;
        for(int cnt=0;cnt<50;cnt++) {
            double mid=(l+r)/2.0;
            for(int i=0;i<n;i++) {
                res[i]=(double)A[i]*100-B[i]*mid;
            }
            sort(res,res+n);
            double sum=0;
            for(int i=n-1;i>=k;i--) {
                sum+=res[i];
            }
            if((sum/100)>-EPS) l=mid;
            else r=mid;
        }
        cout<<(int)(l+0.5)<<endl;
    }
    return 0;
}