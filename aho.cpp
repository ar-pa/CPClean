int nxt[maxn][z], trie[maxn][z], f[maxn], sz = 1;
int insert(string &s){
	int v = 0;
	for(int i = 0; i < s.size(); i++){
		if(!trie[v][s[i] - 'a'])
			trie[v][s[i] - 'a'] = sz++;
		v = trie[v][s[i] - 'a'];
	}
	return v;
}
void aho(){
	int q[maxn] = {};
	int head = 0, tail = 1;
	while(head < tail){
		int v = q[head++];
		for(int i = 0; i < z; i++)
			if(trie[v][i]){
				f[ trie[v][i] ] = nxt[ f[v] ][i];
				nxt[v][i] = trie[v][i];
				q[tail++] = trie[v][i];
			}
			else
				nxt[v][i] = nxt[ f[v] ][i];
	}
}

