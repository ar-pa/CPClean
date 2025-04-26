#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
struct MOS{
	tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag,tree_order_statistics_node_update> os;
	map<T, int> cnt;
	int size(){
		return os.size();
	}
	int order_of_key(const T &x){
		return os.order_of_key({x, 0});
	}
	int ge(int x){
		return os.size() - order_of_key(x);
	}
	void insert(const T &x){
		os.insert({x, cnt[x]++});
	}
	void erase(const T &x){
		os.erase({x, --cnt[x]});
	}
};

struct MOS{
	int fen[maxn], sz, q[maxn];
	int size(){
		return sz;
	}
	int order_of_key(int p){
		int ans = 0;
		for(; p; p ^= p & -p)
			ans += fen[p];
		return ans;
	}
	int bigger(int x){
		return sz - order_of_key(x);
	}
	void insert(int p){
		q[sz++] = p;
		for(p++; p < maxn; p += p & -p)
			fen[p]++;
	}
	void erase(int p){
		for(p++; p < maxn; p += p & -p)
			fen[p]--;
		sz--;
	}
	void reset(int p){
		for(p++; p < maxn; p += p & -p)
			fen[p] = 0;
	}
	void reset(){
		while(sz)
			reset(q[--sz]);
	}
};
