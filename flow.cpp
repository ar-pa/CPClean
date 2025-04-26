struct Flow{
  int tmp,sink,so,sz,*h,*cap,*prv,*to,n;
  bool *mrk;
  Flow(const int &_n=maxn,const int &m=maxn*maxn,const int s=0,const int &snk=1){n=_n,h=new int[n],cap=new int[m],prv=new int[m],to=new int[m],mrk=new bool[m],memset(h,-1,n*sizeof h[0]),memset(mrk,0,n),sink=snk,so=s,sz=0;}
  void add(int v,int u,int vu,int uv=0){to[sz]=u,cap[sz]=vu,prv[sz]=h[v],h[v]=sz++;to[sz]=v,cap[sz]=uv,prv[sz]=h[u],h[u]=sz++;}
  int dfs(const int &v,const int &f=1e9+17){
    if(v==sink)return f;if(mrk[v])return 0;mrk[v]=1;
    for(int i=h[v];i!=-1;i=prv[i])if(cap[i] && (tmp=dfs(to[i],min(f,cap[i]))))return cap[i]-=tmp,cap[i^1]+=tmp,tmp;
    return 0;
  }
  int ans(){int ans=0;for(int tmp;(tmp=dfs(so));ans+=tmp)memset(mrk,0,n);return ans;}
}f;

//be careful about   memset(h,-1,sizeof h);
const int maxn=2e3+17,maxm=maxn*maxn+17,inf=1e9+17;
void add(int v, int u, int vu, int uv = 0){
    to[ecnt] = u, prv[ecnt] = head[v], cap[ecnt] = vu, head[v] = ecnt++;
    to[ecnt] = v, prv[ecnt] = head[u], cap[ecnt] = uv, head[u] = ecnt++;
}
int dfs(int v, int flow = inf){
  if(v == sink || flow == 0)  return f;
  if(mark[v])  return 0;
  mark[v] = 1;
  for(int e = head[v]; e != -1; e = prv[e])
    if(cap[e]){
      int x = dfs(to[e], min(flow, cap[e]));
      if(x)
	return cap[e] -= x, cap[e ^ 1] += x, x;
    }
  return 0;
}
int maxflow(){
  int ans = 0;
  for(int tmp; (tmp=dfs(so)); ans += tmp)
	memset(mark, 0, sizeof mark);
  return ans;
}

// mincost!


namespace F{
	const int maxn = 1e2 + 17, maxm = 1e4 + 17, so = maxn - 1, sink = maxn - 2;
	int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], q[maxm * maxn], ecnt;
	void init(){
		memset(head, -1, sizeof head);
		ecnt = 0;
	}
	void add(int v, int u, int cst = 0, int vu = 1, int uv = 0){
		prv[ecnt] = head[v], to[ecnt] = u, cap[ecnt] = vu, cost[ecnt] = cst, head[v] = ecnt++;
		prv[ecnt] = head[u], to[ecnt] = v, cap[ecnt] = uv, cost[ecnt] = -cst, head[u] = ecnt++;
	}
	int d[maxn], par[maxn];
	bool mark[maxn];
	bool spfa(){
		memset(d, 63, sizeof d);
		d[so] = 0;
		int h = 0, t = 0;
		q[t++] = so, par[so] = -1;
		while(h < t){
			int v = q[h++];
			mark[v] = 0;
			for(int e = head[v]; ~e; e = prv[e])
				if(cap[e] && d[to[e]] > d[v] + cost[e]){
					d[to[e]] = d[v] + cost[e];
					if(!mark[to[e]]){
						mark[to[e]] = 1;
						q[t++] = to[e];
					}
					par[to[e]] = e;
				}
		}
		return d[sink] < 1e9;
	}
	int mincost(){
		int ans = 0;
		while(spfa())
			for(int e = par[sink]; ~e; e = par[to[e ^ 1]])
				cap[e]--, cap[e ^ 1]++, ans += cost[e];
		return ans;
	}
}
//dinic!


namespace F{
	const int maxn = 2e2, maxm = maxn * maxn, inf = 1e9, so = maxn - 1, si = maxn - 2;
	int ptr[maxn], head[maxn], prv[maxm], to[maxm], cap[maxm], d[maxn], q[maxn], ec;
	void init(){
		memset(head, -1, sizeof head);
		ec = 0;
	}
	void add(int v, int u, int vu, int uv = 0){
		to[ec] = u, prv[ec] = head[v], cap[ec] = vu, head[v] = ec++;
		to[ec] = v, prv[ec] = head[u], cap[ec] = uv, head[u] = ec++;
	}
	bool bfs(){
		memset(d, 63, sizeof d);
		d[so] = 0;
		int h = 0, t = 0;
		q[t++] = so;
		while(h < t){
			int v = q[h++];
			for(int e = head[v]; e >= 0; e = prv[e])
				if(cap[e] && d[ to[e] ] > d[v] + 1){
					d[ to[e] ] = d[v] + 1;
					q[t++] = to[e];
					if(to[e] == si)
						return 1;
				}
		}
		return 0;
	}
	int dfs(int v, int f = inf){
		if(v == si || f == 0)
			return f;
		int r = 0;
		for(int &e = ptr[v]; e >= 0; e = prv[e])
			if(d[v] == d[ to[e] ] -1){
				int x = dfs(to[e], min(f, cap[e]));
				f -= x, r += x;
				cap[e] -= x, cap[e ^ 1] += x;
				if(!f)
					break;
			}
		return r;
	}
	int mf(){
		int ans = 0;
		while(bfs()){
			memcpy(ptr, head, sizeof ptr);
			ans += dfs(so);
		}
		return ans;
	}
};
