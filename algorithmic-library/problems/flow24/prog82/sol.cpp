#include <bits/stdc++.h>
using namespace std;

#define cmin(x, y) x = min(x, y)
typedef int ft;
const ft inf = 0x3f3f3f;
const int M = 500000+5,N = 20000+5;

struct SAP{
    int y[M],nxt[M],gap[N],fst[N],c[N],pre[N],q[N],dis[N];
    int vis[N];
    ft f[M];
    int S,T,tot,Tn;
    void init(int s,int t,int tn){
        tot=1;
        memset(fst,0,sizeof (int) * tn);
        memset(dis, 0, sizeof(int) * tn);
        S=s;T=t;Tn=tn;
    }
    int add(int u,int v,ft c1,ft c2=0){
        tot++;y[tot]=v;f[tot]=c1;nxt[tot]=fst[u];fst[u]=tot;
        tot++;y[tot]=u;f[tot]=c2;nxt[tot]=fst[v];fst[v]=tot;
        return tot;
    }
    ft sap(){
        int u=S,t=1;ft flow=0;
        for(int i = 0; i < t; i++){
            int u=q[i];
            for(int j=fst[u];j;j=nxt[j])
                if(dis[y[j]]>dis[u]+1&&f[j^1])
                    q[t++]=y[j],dis[y[j]]=dis[u]+1;
        }
        for(int i = 0; i < Tn; i++)gap[dis[i]]++;
        while(dis[S]<=Tn){
            while(c[u]&&(!f[c[u]]||dis[y[c[u]]]+1!=dis[u]))
                c[u]=nxt[c[u]];
            if(c[u]){
                pre[y[c[u]]]=c[u]^1;
                u=y[c[u]];
                if(u==T){
                    ft minf=inf;
                    for(int p=pre[T];p;p=pre[y[p]])
                        cmin(minf,f[p^1]);
                    for(int p=pre[T];p;p=pre[y[p]])
                        f[p^1]-=minf,f[p]+=minf;
                    flow+=minf;u=S;
                }
            }else {
                if(!(--gap[dis[u]]))break;
                int mind=Tn;
                c[u]=fst[u];
                for(int j=fst[u];j;j=nxt[j])
                    if(f[j]&&dis[y[j]]<mind)
                        mind=dis[y[j]],c[u]=j;
                dis[u]=mind+1;
                gap[dis[u]]++;
                if(u!=S)u=y[pre[u]];
            }
        }
        return flow;
    }
};

char buf[100000];
int main() {
    int n, m;
    scanf("%d%d\n", &m, &n);
    int op = 0, ed = 1;
    SAP s;
    s.init(op, ed, n + m + 10);
    int tot = 0;
    vector<int>value(m, 0);
    for(int i = 0; i < m; i++) {
        gets(buf);
        string ss(buf);
        istringstream line(ss);
        string word;
        int nc = 0;
        while(line >> word) {
            int num = atoi(word.c_str());
            if(nc == 0) {
                s.add(op, ed + i + 1, num);
                tot += num;
                value[i] = num;
            }
            else {
                s.add(ed + i + 1, ed + m + num, inf);
            }
            nc++;
        }
   }
    for(int i = ed + m + 1; i <= ed + m + n; i++) {
        int w;
        scanf("%d", &w);
        s.add(i, ed, w);
    }
    int w = tot - s.sap();
    memset(s.vis, 0, sizeof s.vis);
    queue<int>q;
    q.push(op);
    while(q.size()) {
        int x = q.front(); q.pop();
        s.vis[x] = true;
        for(int k = s.fst[x]; k; k = s.nxt[k]) {
            int v = s.y[k];
            if(!s.vis[v] && s.f[k]) {
                s.vis[v] = true;
                q.push(v);
            }
        }
    }
    for(int i = 1; i <= m; i++)  if(s.vis[ed + i]) printf("%d ", i); puts("");
    for(int i = 1; i <= n; i++) if(s.vis[ed + i + m]) printf("%d ", i); puts("");
    printf("%d\n", w);
    return 0;
}
