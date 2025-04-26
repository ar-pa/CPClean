struct Hash_table {
	int fst[V],nxt[V];
	int T,p;
	void init() {
		T=1; p=0;
	}
	void insert(int s) {
		int S=s%V,j;
		for (j=fst[S];j;j=nxt[j]) if (sta[j]==s) break;
		if (j==0) {
			nxt[T]=fst[S],fst[S]=T,sta[T]=s,ky[T++]=p++;
		}
	}
	int query(int s) {
		for (int j=fst[s%V];j;j=nxt[j]) if (sta[j]==s) return ky[j];
		assert(0);
		return -1;
	}
}Hash;
