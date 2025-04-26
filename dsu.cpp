struct Dsu {
	int par[N];

	Dsu() { memset(par, -1, sizeof par); }

	int root(int v) {
		return par[v] < 0 ? v : par[v] = root(par[v]);
	}

	bool fri(int v, int u) {
		return root(v) == root(u);
	}

	bool merge(int v, int u) {
		if ((v = root(v)) == (u = root(u)))
			return false;
		par[u] += par[v];
		par[v] = u;
		return true;
	}
} dsu;



struct Dsu{
	int par[maxn];
	Dsu(){  memset(par, -1, sizeof par);  }
	int root(int v){
		return par[v] == -1 ? v : par[v] = root(par[v]);
	}
	bool fri(int v, int u){
		return root(v) == root(u);
	}
	bool merge(int v, int u){
		return (v = root(v)) == (u = root(u)) ? 0 : (par[v] = u, 1);
	}
}  dsu;


struct Dsu{
	int par[maxn];
	vector<pair<int, int> > history;
	vector<int> records;
	Dsu(){  memset(par, -1, sizeof par);  }
	void record(){  records.push_back(history.size());  }
	void undo(){
		assert(records.size());
		int when = records.back();  records.pop_back();
		while(history.size() > when){
			int u = history.back().first, sz = history.back().second, v = par[u];
			par[v] -= sz, par[u] = sz;
			history.pop_back();
		}
	}
	int root(int v){
		while(par[v] >= 0)  v = par[v];
		return v;
	}
	bool fri(int v, int u){
		return root(v) == root(u);
	}
	bool merge(int v, int u){
		v = root(v), u = root(u);
		if(v == u)  return 0;
		if(par[v] > par[u])  swap(v, u);
		history.push_back({u, par[u]});
		par[v] += par[u], par[u] = v;
		return 1;
	}
}  dsu;


