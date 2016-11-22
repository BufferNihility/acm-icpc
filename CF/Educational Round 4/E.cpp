#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
#define PII pair<int, int>
#define AA first
#define BB second
#define MP(x, y) make_pair(x, y)
#define LL long long
#define OP begin()
#define ED end()
#define PB(x) push_back(x)
#define SZ size()

const int Maxn = 3000100;
int p[Maxn];
int ans[Maxn];
vector< vector<int> >Q;
vector< int > pos;
int n;

int cmp(int x, int y) {
    return Q[x].SZ < Q[y].SZ;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
    bool flg = false;
    for(int i = 1; i <= n; i++) if(p[i] != -1) {
        int t = i;
        vector<int>f;
        while(p[t] != -1) {
            f.PB(p[t]);
            int tmp = p[t];
            p[t] = -1;
            t = tmp;
        }
        if(f.SZ % 2 == 1) {
            int cnt = (f.SZ + 1) / 2;
            for(int i = 0; i < f.SZ; i++) ans[f[i]] = f[(i + cnt) % f.SZ];
        }
        else {
            Q.PB(f);
        }
    }
    for(int i = 0; i < Q.SZ; i++) pos.PB(i);
    sort(pos.OP, pos.ED, cmp);
    if(Q.SZ % 2 == 1) flg = true;
    else {
        for(int i = 0; i < Q.SZ; i += 2) {
            vector<int> &a = Q[pos[i]], &b = Q[pos[i + 1]];
            if(a.SZ != b.SZ) { flg = true; break; }
            else {
                for(int i = 0; i < a.SZ; i++) ans[a[i]] = b[i];
                for(int i = 0; i < b.SZ - 1; i++) ans[b[i]] = a[i + 1];
                ans[b[b.SZ - 1]] = a[0];
            }
        }
    }
    if(flg) puts("-1");
    else for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}
