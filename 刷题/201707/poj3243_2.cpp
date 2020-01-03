#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;
typedef __int64_t ll;

//map<int, int> EP;

const int maxn = 500007;
int h[maxn], EP[maxn];

bool insert(int x, int k){
    int p = (x << 6) % maxn;

    if (p < 0) p += maxn;
    while (h[p] != x && ~EP[p]) p = (p + 1) % maxn;

    if (h[p] == x && ~EP[p]) return false;

    h[p] = x;
    EP[p] = k;

    return true;
}

int find(int x){
    int p = (x << 6) % maxn;

    if (p < 0) p += maxn;
    while (h[p] != x && ~EP[p]) p = (p + 1) % maxn;

    return EP[p];
}

int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}

void exgcd(int a, int b, ll &x, ll &y){
    if (b){
        exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else{
        x = 1;
        y = 0;
    }
}

int multiMod(int a, int b, int m){
    int ret = 0;

    while (b){
        if (b & 1) ret += a, ret %= m;
        a <<= 1;
        a %= m;
        b >>= 1;
    }

    return ret;
}

int powMod(int p, int n, int m){
    int ret = 1;

    while (n){
        if (n & 1) ret = multiMod(ret, p, m);
        p = multiMod(p, p, m);
        n >>= 1;
    }

    return ret;
}

int babyStep(int &p, int &m, int &rest, int &base, int &mark){
    // return 0: cnt is answer
    // return -1: no solution
    // return else: base counts before steps, and mark is base-pow and return size
    int t, cur = 1 % m;

    mark = 1 % m;
    base = 0;
//    EP.clear();
    memset(EP, -1, sizeof(EP));
    while ((t = gcd(p, m)) != 1){
        if (rest % t) return -1;
        base++;
        m /= t;
        rest /= t;
        mark = multiMod(mark, p / t, m);
    }

    int r = (int) ceil(sqrt((double) m));

    cur = 1 % m;
    for (int i = 0; i <= r; i++){
//        if (EP.count(cur)) break;
//        EP[cur] = i;
        if (!insert(cur, i)) break;
        cur = multiMod(cur, p, m);
    }

    return r;
}

int giantStep(int p, int m, int rest){
    //if (rest >= m) return -1;
    
    rest %= m;
    for (int i = 0, cur = 1 % m; i <= 50; i++){ // before baby-step try whether there is a simple solution
        if (cur == rest){
            return i;
        }
        cur = multiMod(cur, p, m);
    }

    int tmp, cnt;
    int r = babyStep(p, m, rest, cnt, tmp);

    if (r == -1) return -1;

    int ep = powMod(p, r, m); // cycle-length

    if (!r)    return cnt;
    for (int i = 0; i <= r; i++){
        ll x, y;

        exgcd(tmp, m, x, y);
        x = multiMod(x, rest, m);
        if (x < 0) x += m;
//        if (EP.count((int)x)){
//            return EP[(int)x] + i * r + cnt;
//        }
        int f = find((int)x);

        if (~f) return f + i * r + cnt;
        tmp = multiMod(tmp, ep, m);
    }

    return -1;
}

int main(){
    int k, p, n;

    while (~scanf("%d%d%d", &k, &p, &n) && (k || p || n)){
        int ans = giantStep(k, p, n);

        if (~ans && ans < p) printf("%d\n", ans);
        else puts("No Solution");
    }

    return 0;
}