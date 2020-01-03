#include <bits/stdc++.h>
int m, n, p[20], c[20], ans;
const int to[20] = {0, 13, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int calc(void) {
    register int res = 0;
    memset(c, 0, sizeof(c));
    for (int i = 0; i <= 13; ++i)++c[p[i]];
    while (c[4] > 0 && c[2] > 1)c[4] -= 1, c[2] -= 2, ++res;
    while (c[4] > 0 && c[1] > 1)c[4] -= 1, c[1] -= 2, ++res;
    while (c[4] > 0 && c[2] > 0)c[4] -= 1, c[2] -= 1, ++res;
    while (c[3] > 0 && c[2] > 0)c[3] -= 1, c[2] -= 1, ++res;
    while (c[3] > 0 && c[1] > 0)c[3] -= 1, c[1] -= 1, ++res;
    return res + c[1] + c[2] + c[3] + c[4];
}
void search(int s) {
    if (s >= ans)return;
    ans = std::min(ans, s + calc());
    for (int i = 2, pos, tot; i <= 13; ++i)
        for (int j = 1; j <= 3; ++j)if (p[i] >= j) {
            for (pos = i, tot = 0; p[pos] >= j; ++pos)p[pos] -= j, tot += j;
            for (; --pos >= i; p[pos] += j, tot -= j)if (tot >= 5)search(s + 1);
        }
}
signed main(void) {
    scanf("%d%d", &m, &n);
    while (m--) {
        memset(p, 0, sizeof(p));
        for (int i = 1, x; i <= n; ++i)
            scanf("%d%*d", &x), ++p[to[x]];
        ans = 100, search(0), printf("%d\n", ans);
    }
}

