#include<iostream>
#include<algorithm>
#define N 1000005
using namespace std;

int s1[N],s2[N],sum[N],pre[N];
int t1,t2;

int main()
{
    cin.sync_with_stdio(false);
    while(1) {
        int T;
        cin>>T;
        if(cin.eof()) break;
        t1=t2=0;
        pre[0]=-1000000;
        while(T--) {
            char cmd;
            int val;
            cin>>cmd;
            switch(cmd) {
                case 'I':
                    cin>>val;
                    s1[t1++]=val;
                    sum[t1]=sum[t1-1]+s1[t1-1];
                    pre[t1]=max(pre[t1-1],sum[t1]);
                    break;
                case 'Q':
                    cin>>val;
                    cout<<pre[val]<<endl;
                    break;
                case 'L':
                    if(t1==0) break;
                    s2[t2++]=s1[--t1];
                    break;
                case 'D':
                    if(t1==0) break;
                    t1--;
                    break;
                case 'R':
                    if(t2==0) break;
                    s1[t1++]=s2[--t2];
                    sum[t1]=sum[t1-1]+s1[t1-1];
                    pre[t1]=max(pre[t1-1],sum[t1]);
                    break;
            }
            cin.get();
        }
    }
    return 0;
}