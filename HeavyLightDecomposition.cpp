// In the name of Allah.
// We're nothing and you're everything.
// Ya Ali!
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 14;

struct Edge {
  int v, u, w;
} edges[MAX_N];

int n, head[MAX_N], h[MAX_N], sz[MAX_N], st[MAX_N], seg[MAX_N * 2], par[MAX_N];
vector<int> g[MAX_N];

void update(int i, int x) {  // changes value of i'th element to x
  for (seg[i += n] = x; i >>= 1;)
    seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
}

int get(int l, int r) {  // returns the maximum value of segment [l, r)
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      ans = max(ans, seg[l++]);
    if (r & 1)
      ans = max(ans, seg[--r]);
  }
  return ans;
}

int go(int v, int u) {
  int ans = 0;
  while (head[v] != head[u]) {
    if (h[head[v]] < h[head[u]])
      swap(v, u);
    if (head[v] == v) {
      ans = max(ans, get(st[v], st[v] + 1));
      v = par[v];
    }
    else {
      ans = max(ans, get(st[head[v]] + 1, st[v] + 1));
      v = head[v];
    }
  }
  if (h[v] < h[u])
    swap(v, u);
  ans = max(ans, get(st[u] + 1, st[v] + 1));
  return ans;
}

void make_order(int v = 0) {
  sz[v] = 1;
  for (int u: g[v]) {
    g[u].erase(find(g[u].begin(), g[u].end(), v));
    h[u] = h[v] + 1;
    make_order(u);
    sz[v] += sz[u];
  }
  if (!g[v].empty())
    swap(g[v][0], *max_element(g[v].begin(), g[v].end(), [](int v, int u) {
      return sz[v] < sz[u];
    }));
}

void make_hld(int v = 0) {
  static int time;
  if (v == 0)
    time = 0;
  st[v] = time++;
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    head[u] = i == 0 ? head[v] : u;
    make_hld(u);
    par[u] = v;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    fill(seg, seg + 2 * n, 0);
    fill(g, g + n, vector<int>());
    for (int i = 0; i < n - 1; ++i) {
      cin >> edges[i].v >> edges[i].u >> edges[i].w;
      --edges[i].v;
      --edges[i].u;
      g[edges[i].v].push_back(edges[i].u);
      g[edges[i].u].push_back(edges[i].v);
    }
    make_order();
    make_hld();
    for (int i = 0; i < n - 1; ++i) {
      if (h[edges[i].v] > h[edges[i].u])
        swap(edges[i].v, edges[i].u);
      update(st[edges[i].u], edges[i].w);
    }
    while (true) {
      string type;
      cin >> type;
      if (type == "CHANGE") {
        int i, ti;
        cin >> i >> ti;
        --i;
        update(st[edges[i].u], ti);
      }
      else if (type == "QUERY") {
        int v, u;
        cin >> v >> u;
        --v;
        --u;
        cout << go(v, u) << '\n';
      }
      else
        break;
    }
  }

}
