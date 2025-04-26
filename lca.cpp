// In the name of Allah.
// We're nothing and you're everything.
// Ya Ali!

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 14, LG = 18;

int n, h[N], par[LG][N];
vector<int> g[N];
void dfs(int v = 0, int p = -1){
	for(int u : g[v])
		if(u != p){
			par[0][u] = v;
			h[u] = h[v] + 1;
			dfs(u, v);
		}
}

int lca(int v, int u){
	if(h[v] > h[u])
		swap(v, u);
	for(int i = 0; i < LG; i++)
		if(h[u] - h[v] >> i & 1)
			u = par[i][u];
	for(int i = LG - 1; i >= 0; i--)
		if(par[i][v] != par[i][u])
			v = par[i][v], u = par[i][u];
	return v == u ? v : par[0][v];
}

int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        int v, u;
        cin >> v >> u;
        v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs();
    for(int k = 1; k < LG; k++)
        for(int i = 0; i < n; i++)
            par[k][i] = par[k - 1][ par[k - 1][i] ];

}
