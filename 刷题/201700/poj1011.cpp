#include <iostream>
#include <algorithm>
#define N 70
using namespace std;

int n,sum,L,rem;
int len[N];
bool used[N];

bool solve(int last,int l)
{
    if(rem==0) {
        if(rem==0) return true;
        for(int i=0;i<n;i++) {
            if(!used[i]) return solve(i,L-len[i]);
        }
        return false;
    } 
    for(int i=last+1;i<n;i++) {
        if(used[i]||len[i]>l||(i>last+1&&!used[i-1]&&len[i-1]==len[i])) continue;
        used[i]=true;
        rem--;
        if(solve(i,l-len[i])) return true;
        used[i]=false;
        rem++;
    }
    return false;
}

int main()
{
    cin>>n;
    rem=n;
    for(int i=0;i<n;i++) {
        cin>>len[i];
        sum+=len[i];
    }
    sort(len,len+n,greater<int>());
    for(L=1;L<=N;L++) {
        if(!sum%L) continue;
        if(solve(-1,L)) {
            cout<<L<<endl;
            return 0;
        }
    }
    return 0;
}
