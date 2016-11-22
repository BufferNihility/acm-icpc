#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;
typedef unsigned u32;
#define Maxn 200000
#define Mpow 20
#define MP make_pair
#define AA first
#define BB second


typedef pair<u32, u32> obj;
typedef long long LL;
u32 c[Maxn];
u32 rmq[Maxn][Mpow];
u32 xsum[Maxn];
obj index[Maxn];

int n;

struct Q {
    int l, r;
    u32 c;
    Q(){}
    Q(int l, int r, u32 c): l(l), r(r), c(c) {}
}qry[Maxn * 32]; int tot;


int cmp(Q a, Q b) {
    if(a.c == b.c) return MP(a.l, a.r) < MP(b.l, b.r);
    return a.c < b.c;
}

void make() {
    for(int i = 1; i <= n; i++) rmq[i][0] = c[i];
    for(int j = 1; j < Mpow; j++) for(int i = 1; i <= n; i++) {
        if(i + (1 << j) <= n + 1) {
            rmq[i][j] = (rmq[i][j - 1]) & (rmq[i + (1 << (j - 1))][j - 1]);
        }
    }
}

u32 st(int l, int r) {
    int k = log2(r - l + 1);
    return rmq[l][k] & rmq[r - (1 << k) + 1][k];
}

int main() {
    freopen("hack.in", "r", stdin);
    freopen("hack.out", "w", stdout);

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%u", &c[i]);
    }
    make();
    xsum[0] = 0;
    for(int i = 1; i <= n; i++) xsum[i] = xsum[i - 1] ^ c[i];

    tot = 0;
    for(int i = 1; i <= n; i++) {
        int p = i;
        while(p != n + 1) {
            u32 s = st(i, p);
            int l = p, r = n;
            while(l < r) {
                int mid = (l + r + 1) / 2;
                if(st(i, mid) == s) l = mid;
                else r = mid - 1;
            }
            qry[tot++] = Q(p, l, s ^ xsum[i - 1]);
            assert(tot < Maxn * 32);
            p = l + 1;
        }
    }



    for(int i = 1; i <= n; i++) index[i - 1] = MP(xsum[i], i);
    sort(index, index + n);
    LL ans = 0;
    for(int i = 0; i < tot; i++) {
//        cout << qry[i].l << " " << qry[i].r << " " << qry[i].c;
        int l = lower_bound(index, index + n, MP((u32)qry[i].c, (u32)qry[i].l)) - index;
        int r = upper_bound(index, index + n, MP((u32)qry[i].c, (u32)qry[i].r)) - index;
//        cout << " " << (r - l) << endl;
        ans += (LL)(r - l);
    }
    printf("%I64d\n", ans);
    return 0;
}
