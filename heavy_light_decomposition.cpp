// In the name of God.
// You're anything and We're nothing.
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 17, lg = 17;
int n, q, col[maxn], head[maxn], par[lg][maxn], h[maxn], st[maxn], ft[maxn], iman[maxn << 2], sina[maxn << 2];
vector<int> g[maxn];
pair<int, int> qu[maxn];
int prep(int v = 0, int p = -1){
	if(g[v].empty() || g[v].size() == 1 && g[v][0] == p){
		col[v] = head[v] = v;
		return 1;
	}
	int sz = 1, big, mx = 0;
	for(int i = 0; i < g[v].size(); i++){
		int u = g[v][i];
		if(u == p)  continue;
		par[0][u] = v;
		h[u] = h[v] + 1;
		int s = prep(u, v);
		sz += s;
		if(s > mx)
			mx = s, big = i;
	}
	col[v] = col[ g[v][big] ];
	head[ col[v] ] = v;
	swap(g[v][0], g[v][big]);
	return sz;
}
void get_st(int v = 0){
	static int time = 0;
	st[v] = time++;
	for(auto u : g[v])
		if(u != par[0][v])
			get_st(u);
	ft[v] = time;
}
int lca(int v, int u){
	if(h[u] < h[v])
		swap(v, u);
	for(int i = 0; i < lg; i++)
		if(h[u] - h[v] >> i & 1)
			u = par[i][u];
	for(int i = lg - 1; i >= 0; i--)
		if(par[i][v] != par[i][u])
			v = par[i][v], u = par[i][u];
	return v == u ? v : par[0][v];
}
int dis(int v, int u){
	return h[v] + h[u] - 2 * h[lca(v, u)];
}
void sadra(int id){
	if(sina[id] == -1)
		return;
	iman[id << 1] = iman[id << 1 | 1] = sina[id << 1] = sina[id << 1 | 1] = sina[id];
	sina[id] = -1;
}
void majid(int s, int e, int x, int l = 0, int r = n, int id = 1){
	if(s <= l && r <= e){
		iman[id] = sina[id] = x;
		return ;
	}
	if(e <= l || r <= s)  return ;
	sadra(id);
	int mid = l + r >> 1;
	majid(s, e, x, l, mid, id << 1);
	majid(s, e, x, mid, r, id << 1 | 1);
	iman[id] = max(iman[id << 1], iman[id << 1 | 1]);
}
int hamid(int s, int e, int l = 0, int r = n, int id = 1){
	if(s <= l && r <= e)  return iman[id];
	if(e <= l || r <= s)  return 0;
	sadra(id);
	int mid = l + r >> 1;
	return max(hamid(s, e, l, mid, id << 1), hamid(s, e, mid, r, id << 1 | 1));
}
void change(int v, int u, int x){
	//cerr << "changeing " << v << ' ' << u << ' ' << x << '\n';
	if(col[v] == col[u]){
		majid(st[u], st[v] + 1, x);
		return ;
	}
	if(col[v] != col[ par[0][v] ]){
		majid(st[v], st[v] + 1, x);
		change(par[0][v], u, x);
		return ;
	}
	majid(st[ head[ col[v] ] ], st[v] + 1, x);
	change(par[0][ head[ col[v] ] ], u, x);
}
void Change(int v, int u, int x){
	int p = lca(v, u);
	change(v, p, x);
	change(u, p, x);	
}
int get_max(int v, int u){
	if(col[v] == col[u])
		return hamid(st[u], st[v] + 1);
	if(col[v] != col[ par[0][v] ])
		return max(hamid(st[v], st[v] + 1), get_max(par[0][v], u));
	return max(hamid(st[ head[ col[v] ] ], st[v] + 1), get_max(par[0][ head[ col[v] ] ], u));
}
int Get_max(int v, int u){
	int p = lca(v, u);
	return max(get_max(v, p), get_max(u, p));	
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	memset(sina, -1, sizeof sina);
	cin >> n >> q;
	for(int i = 1, v, u; i < n; i++){
		cin >> v >> u;
		v--, u--;
		g[v].push_back(u);
		g[u].push_back(v);		
	}
	for(int i = 0; i < q; i++){
		cin >> qu[i].first >> qu[i].second;
		qu[i].first--, qu[i].second--;
	}
	prep();
	get_st();
	for(int i = 1; i < lg; i++)
		for(int v = 0; v < n; v++)
			par[i][v] = par[i - 1][ par[i - 1][v] ];
	sort(qu, qu + q, [](pair<int, int> a, pair<int, int> b){
			return dis(a.first, a.second) < dis(b.first, b.second);
		});
	for(int i = 0; i < q; i++){
		int v = qu[i].first, u = qu[i].second, p = lca(v, u);
		for(int j = Get_max(v, u); j; j = Get_max(v, u)){
			int x = qu[j - 1].first, y = qu[j - 1].second, p2 = lca(x, y);
			bool ok = st[p] <= st[x] && ft[x] <= ft[p];
			ok &= st[p] <= st[y] && ft[y] <= ft[p];
			ok &= st[x] <= st[v] && ft[v] <= ft[x] || st[x] <= st[u] && ft[u] <= ft[x];
			ok &= st[y] <= st[v] && ft[v] <= ft[y] || st[y] <= st[u] && ft[u] <= ft[y];
			if(!ok){
				//cerr << "confil: " << v << ' ' << u << " with " << x << ' ' << y << '\n';
				return cout << "No\n", 0;
			}
			Change(x, y, 0);
		}
		Change(v, u, i + 1);
	}
	cout << "Yes\n";
}
