﻿/*
 * 点修改区间查询
 */
#include <bits/stdc++.h>
const int N = 5000;
int c[N][N];
int lx[N], ly[N];
int n, Q;
struct Node
{
  struct node
  {
    int a, b;
    int Min, Max;
  }f[N];
  int a, b;

  void update(int x)
  {
    f[x].Min = std::min(f[x << 1].Min, f[x << 1 | 1].Min);
    f[x].Max = std::max(f[x << 1].Max, f[x << 1 | 1].Max);
  }

  void build(int x, int a, int b)
  {
    f[x].a = a; f[x].b = b;
    if(a < b)
    {
      int mid = (a + b) / 2;
      build(x << 1, a, mid);
      build(x << 1 | 1, mid + 1, b);
      update(x);
    } else { f[x].Min = f[x].Max = 0; ly[a] = x; }
  }

  int queryMin(int x, int a, int b)
  {
    if(a <= f[x].a && f[x].b <= b) return f[x].Min;
    else
    {
      int mid = (f[x].a + f[x].b) / 2;
      if(b <= mid) return queryMin(x << 1, a, b);
      else if(a > mid) return queryMin(x << 1 | 1, a, b);
      else return std::min(queryMin(x << 1, a, b), queryMin(x << 1 | 1, a, b));
    }
  }

  int queryMax(int x, int a, int b)
  {
    if(a <= f[x].a && f[x].b <= b) return f[x].Max;
    else
    {
      int mid = (f[x].a + f[x].b) / 2;
      if(b <= mid) return queryMax(x << 1, a, b);
      else if(a > mid) return queryMax(x << 1 | 1, a, b);
      else return std::max(queryMax(x << 1, a, b), queryMax(x << 1 | 1, a, b));
    }
  }
}f[N];

void build(int x, int a, int b, int p, int q)
{
  f[x].a = a; f[x].b = b;
  f[x].build(1, p, q);
  if(a < b)
  {
    int mid = (a + b) / 2;
    build(x << 1, a, mid, p, q);
    build(x << 1 | 1, mid + 1, b, p, q);
  }
  else lx[a] = x;
}

void update(int x, int y, int c)
{
  x = lx[x]; y = ly[y];
  for(int X = x; X != 0; X >>= 1)
    for(int Y = y; Y != 0; Y >>= 1)
    {
      if(f[X].f[Y].a == f[X].f[Y].b)
      {
        if(f[X].a == f[X].b)
        {
          f[X].f[Y].Min = f[X].f[Y].Max = c;
        }
        else
        {
          f[X].f[Y].Min = std::min(f[X << 1].f[Y].Min, f[X << 1 | 1].f[Y].Min);
          f[X].f[Y].Max = std::max(f[X << 1].f[Y].Max, f[X << 1 | 1].f[Y].Max);
        }
      }
      else { f[X].update(Y); }
    }
}

int queryMin(int x, int a, int b, int p, int q)
{
  if(a <= f[x].a && f[x].b <= b) return f[x].queryMin(1, p, q);
  else
  {
        int mid = (f[x].a + f[x].b) / 2;
        if(b <= mid) return queryMin(x << 1, a, b, p, q);
        else if(a > mid) return queryMin(x << 1 | 1, a, b, p, q);
        else return std::min(queryMin(x << 1, a, b, p, q), queryMin(x << 1 | 1, a, b, p, q));
    }
}

int queryMax(int x, int a, int b, int p, int q)
{
    if(a <= f[x].a && f[x].b <= b) return f[x].queryMax(1, p, q);
    else
    {
        int mid = (f[x].a + f[x].b) / 2;
        if(b <= mid) return queryMax(x << 1, a, b, p, q);
        else if(a > mid) return queryMax(x << 1 | 1, a, b, p, q);
        else return std::max(queryMax(x << 1, a, b, p, q), queryMax(x << 1 | 1, a, b, p, q));
    }
}

