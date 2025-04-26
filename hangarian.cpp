template <typename WMT> struct Hungarian{
	static const int maxn = 60;
	static const WMT WMINF = WMT(1 << 29);
	bool S[maxn], T[maxn];
	int prv[maxn], mx[maxn], my[maxn], x, y, matched, slx[maxn];
	WMT lx[maxn], ly[maxn], w[maxn][maxn], n, slack[maxn];
	inline void init(int _n, WMT _w[][maxn]){
		n = _n;
		For(i,0,n)	For(j,0,n)	w[i][j] = _w[i][j];
	}
	inline void add_to_tree(int x, int p){
		S[x] = true;
		prv[x] = p;
		For(y, 0, n)
			if(slack[y] > lx[x] + ly[y] - w[x][y])
				slack[y] = lx[x] + ly[y] - w[x][y], slx[y] = x;
	}
	inline void AgumentInit(){
		memset(S, false, n * sizeof S[0]);
		memset(T, false, n * sizeof T[0]);
		memset(prv, -1, sizeof prv);
		For(j,0,n){
			slack[j] = WMINF;
			slx[j] = -1;
		}
	}
	inline void update_lables(){
		WMT delta = WMINF;
		For(i,0,n)	
			if(!T[i])
				smin(delta, slack[i]);
		For(i,0,n){
			if(S[i])
				lx[i] -= delta;
			if(T[i])
				ly[i] += delta;
			else
				slack[i] -= delta;
		}
	}
	inline void agument(){
		if(matched == n)	return ;
		AgumentInit();
		static int qu[maxn], head, tail;
		head = tail = 0;
		for(x = 0; x < n; x ++)
			if(mx[x] == -1){
				add_to_tree(x, -1);
				qu[tail ++] = x;
			}
		while(true){
			while(head < tail){
				x = qu[head ++];
				for(y = 0; y < n; y ++)	if(w[x][y] == lx[x] + ly[y] && !T[y]){
					if(my[y] == -1)
						break;
					T[y] = true;
					add_to_tree(my[y], x);
					qu[tail ++] = my[y];
				}
				if(y < n)	break;
			}
			if(y < n)	break;
			update_lables();
			for(y = 0; y < n;y ++)
				if(!T[y] && !slack[y]){
					x = slx[y];
					if(my[y] == -1)
							break ;
					T[y] = true;
					if(!S[my[y]]){
						add_to_tree(my[y], x);
						qu[tail ++] = my[y];
					}
				}
			if(y < n)	break ;
		}
		if(y >= n)	return ;
		++ matched;
		while(x + 1 && y + 1){
			int z = mx[x];
			mx[x] = y, my[y] = x;
			x = prv[x], y = z;
		}
		agument();
	}
	inline WMT hungarian(){
		memset(lx, 0, n * sizeof lx[0]);
		memset(ly, 0, n * sizeof ly[0]);
		memset(mx, -1, sizeof mx);
		memset(my, -1, sizeof my);
		matched = 0;
		For(i,0,n)
			For(j,0,n)
				smax(lx[i], w[i][j]);
		AgumentInit();
		agument();
		WMT ans = 0;
		For(i,0,n)
			ans += w[i][mx[i]];
		return ans;
	}
};
