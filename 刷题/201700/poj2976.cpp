#include <iostream>
#include <algorithm>
#define N 1005
using namespace std;

int A[N],B[N];
double res[N];

int main()
{
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
        double l=0,r=1;
        for(int cnt=0;cnt<60;cnt++) {
            double mid=(l+r)/2;
            for(int i=0;i<n;i++) {
                res[i]=A[i]-B[i]*mid;
            }
            sort(res,res+n);
            double sum=0;
            for(int i=n-1;i>=k;i--) {
                sum+=res[i];
            }
            if(sum>=0) l=mid;
            else r=mid;
        }
        cout<<(int)((l+r)*50)<<endl;
    }
    return 0;
}
