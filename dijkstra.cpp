const int maxn = 1e5, inf = 2e9;
vector<pair<int, int> > g[maxn];
set<pair<int, int> > pq;
int d[maxn];
void dij(int source){
	fill(d, d + n, inf);
	d[source] = 0;
	pq.insert({0, source});
	while(pq.size()){
		int v = pq.begin() -> second;  
		pq.erase(pq.begin());
		for(auto e : g[v])
			if(d[e.first] > d[v] + e.second){
				pq.erase({d[e.first], e.first});
				pq.insert({d[e.first] = d[v] + e.second, e.first});
			}
	}
}

