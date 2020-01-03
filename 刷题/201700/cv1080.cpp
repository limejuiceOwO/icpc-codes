#include<cstdio>

long long bit[100001];
int n;

void alt(int idx,long long v) {
    while(idx<=n) {
        bit[idx]+=v;
        idx+=(idx&-idx);
    }
}

long long lookup(int idx) {
    long long ans=0;
    while(idx) {
         ans+=bit[idx];
         idx-=(idx&-idx);
    }
    return ans;
}

int main() {
    int m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        int v;
        scanf("%d",&v);
        alt(i,v);
    }
    scanf("%d",&m);
    while(m--) {
        int c,a,b;
        scanf("%d%d%d",&c,&a,&b);
        if(c==1) {
            alt(a,b);
        } else {
            printf("%lld\n",lookup(b)-lookup(a-1));
        }
    }
    return 0;
}
