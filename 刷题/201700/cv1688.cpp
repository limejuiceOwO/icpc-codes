#include <bits/stdc++.h>
#define N 1000005
using namespace std;

int arr[N],tmp[N];
int n;

long long merge_count(int l,int r)
{
    if(r-l<=1) return 0;
    int mid=l+((r-l)>>1);
    long long ans=merge_count(l,mid)+merge_count(mid,r);
    for(int i=l,j=mid,k=0;k<r-l;k++) {
        if(j<r&&(i>=mid||arr[i]>arr[j])) {
            tmp[k]=arr[j++];
            ans+=(mid-i);
        } else {
            tmp[k]=arr[i++];
        }
    }
    memcpy(arr+l,tmp,(r-l)*sizeof(int));
    return ans;
}

int main()
{
    cin.sync_with_stdio(false);
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }
    cout<<merge_count(0,n)<<endl;
    return 0;
}