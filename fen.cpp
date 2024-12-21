struct DF{
	int *fen, sz;
	vector<int> all;
	void pre(int x){
		all.push_back(x);
	}
	void init(){
		sort(all.begin(), all.end());
		all.resize(unique(all.begin(), all.end()) - all.begin());
		sz = all.size() + 1;
		fen = new int[sz];
		memset(fen, 0, sz * 4);
	}
	int hamid(int x){
		x = lower_bound(all.begin(), all.end(), x) - all.begin();
		int ans = 0;
		for(; x; x ^= x & -x)
			ans += fen[x];
		return ans;
	}
	void majid(int x){
		x = lower_bound(all.begin(), all.end(), x) - all.begin();
		for(x++; x < sz; x += x & -x)
			fen[x]++;
	}
};

// Update : element, Get : range
int fen[maxn];
int get(int p){
	int ans = 0;
	for(; p; p ^= p & -p)  ans += fen[p];
	return ans;
}
int get(int l, int r){  // returns sum of range [l, r)
	return get(r) - get(l);
}
void upd(int p, int v){  // adds v to p'th element
	for(p++; p < maxn; p += p & -p)  fen[p] += v;
}

// Update : range, Get : element
int fen[maxn];
int get(int p){
	int ans = 0;
	for(p++; p; p ^= p & -p)  ans += fen[p];
	return ans;
}
void upd(int p, int v){
	for(p++; p < maxn; p += p & -p)  fen[p] += v;
}
void upd(int l, int r, int v){  // adds v to range [l, r)
	upd(l, v), upd(r, -v);
}
