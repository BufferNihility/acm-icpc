#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define LL long long
#define cmax(x, y) x = max(x, y)
#define PII pair<int, int>
#define AA first
#define BB second
#define MP(x, y) make_pair(x, y)
#define PB(x) push_back(x)
#define SZ size()
#define LEN(Q) (Q.BB - Q.AA + 1)
vector<int>f;
char s[100100];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> s;
    int pre = 0;
    for(int i = 1; i < n; i++) if(s[i] != s[i - 1]) {
        f.PB(i - pre);
        pre = i;
    }
    f.PB(n - pre);
    int ans = f.SZ;
    for(int i = 0; i < f.SZ; i++) if(f[i] > 2) cmax(ans, (int)f.SZ + 2);
    int cnt = 0;
    int flg1 = false;
    for(int i = 0; i < f.SZ; i++) if(f[i] >= 2) cnt++;
    for(int i = 1; i < f.SZ; i++) if(f[i] >= 2 && f[i - 1] >= 2) flg1 = true;

    if(cnt) cmax(ans, (int)f.SZ + 1);
    if(cnt >= 2) cmax(ans, (int)f.SZ + 2);
    cout << ans << endl;
    return 0;
}

