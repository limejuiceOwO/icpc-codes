int fastpow(int base,long long p,int mod)
{
    long long b=base,ans=1;
    while(p) {
        if(p&1) ans=(ans*b)%mod;
        p>>=1;
        b=(b*b)%mod;
    }
}
