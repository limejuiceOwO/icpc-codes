#include <iostream>
#include <algorithm>
#define LGN 77
#define M 1000000000
using namespace std;

long long seg[LGN][LGN][LGN];
long long dp[LGN][LGN];

int main()
{
    long long x;
    int lgx=0;
    //cin>>lgx;
    cin>>x;
    while(((unsigned long long)1<<lgx)<x) lgx++;
    for(int i=0;i<=lgx;i++) seg[i][i][i]=1;

    for(int i=1;i<=lgx;i++) {
        for(int j=0;j<i;j++) {
            for(int k=j;k<i;k++) {
                for(int l=j-1;l<=k;l++) {
                    for(int m=l;m<=k;m++) {
                        seg[i][j][k]=(seg[i][j][k]+seg[i-1][j][l]*seg[i-1][m][k])%M;
                    }
                }
            }
        }
    }
    /*
    for(int j=0;j<=lgx;j++) {
        for(int k=0;k<=lgx;k++) {
            cout<<"("<<j<<","<<k<<") ";
            for(int i=0;i<=lgx;i++) {
                cout<<seg[i][j][k]<<" ";
            }
        cout<<endl;
        }
    }
    */
    int i=0,last=0;
    while(!(x&1)) x>>=1,i++;
    for(int j=0;j<=lgx;j++) {
        if(j) dp[i][j]=dp[i][j-1];
        for(int k=0;k<=j;k++) dp[i][j]=(dp[i][j]+seg[i][k][j])%M;
    }
    last=i;
    x>>=1,i++;
    while(x) {
        while(!(x&1)) x>>=1,i++;
        //cout<<"''"<<i<<endl;
        for(int j=0;j<=lgx;j++) {
            if(j) dp[i][j]=dp[i][j-1];
            for(int k=0;k<=j;k++) {
                //cout<<"'"<<last<<" "<<k<<" "<<dp[last][k]<<" "<<seg[i][k][j]<<endl;
                dp[i][j]=(dp[i][j]+dp[last][k]*seg[i][k][j])%M;
            }
        }
        last=i;
        x>>=1,i++;
    }
    cout<<dp[i-1][i-1]<<endl;
    return 0;
}