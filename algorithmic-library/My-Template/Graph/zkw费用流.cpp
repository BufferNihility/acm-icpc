/*
 * luoshiying 版本
 * 使用前需要给$src, des$赋值
 * 调用$zkw(src, des, n)$中的$tn$为节点数目，要稍大于总数目
 */
#include <bits/stdc++.h>
#define MOD 0x3f3f3f3f
const int Maxn = 3000;
const int Maxm = 100000;
struct edge
{
  int u, v, c, w, next;
}e[Maxm];
int last[Maxn];
int tot;
int flow, cost, value;
int dist[Maxn], visit[Maxn], src, des;
std::deque<int> Q;
int n, m;

void adde(int u, int v, int c, int w) {
  e[tot].u = u; e[tot].v = v; e[tot].c = c; e[tot].w = w; e[tot].next = last[u]; last[u] = tot++;
  e[tot].u = v; e[tot].v = u; e[tot].c = 0; e[tot].w = -w; e[tot].next = last[v]; last[v] = tot++;
}

int Aug(int u, int m) {
  if(u == des) {
    cost += value * m;
    flow += m;
    return m;
  }
  visit[u] = true;
  int l = m;
  int j, v, c, w;
  for(j = last[u]; j != -1; j = e[j].next) {
    v = e[j].v; c = e[j].c; w = e[j].w;
    if(c && !w && !visit[v]) {
      int del = Aug(v, l < c ? l : c);
      e[j].c -= del; e[j ^ 1].c += del; l -= del;
      if(!l) return m;
    }
  }
  return m - l;
}

bool Modlabel(int src, int des, int n) {
  int i, j, u, v, c, w, del;
  memset(dist, 0x3f, sizeof(dist[0])*(n + 3));
  dist[src] = 0;
  while(!Q.empty()) Q.pop_back();
  Q.push_back(src);
  while(!Q.empty()) {
    u = Q.front(); Q.pop_front();
    for(j = last[u]; j != -1; j = e[j].next) {
      v = e[j].v; c = e[j].c; w = e[j].w;
      if(c && (del = dist[u] + w) < dist[v]) {
        dist[v] = del;
        if(Q.empty() || del <= dist[Q.front()]) {
          Q.push_front(v);
        }
        else {
          Q.push_back(v);
        }
      }
    }
  }
  for(i = 0; i < n; i++) {
    for(j = last[i]; j != -1; j = e[j].next) {
      e[j].w -= dist[e[j].v] - dist[i];
    }
  }
  value += dist[des];
  return dist[des] < MOD;
}

void zkw(int src, int des, int n) {
  value = cost = flow = 0;
  while(Modlabel(src, des, n)){
    do {
      memset(visit, 0, sizeof(visit[0]) * (n + 3));
    }while(Aug(src, MOD));
  }
}
