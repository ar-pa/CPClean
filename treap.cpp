// In the name of Allah.
// We're nothing and you're everything.
// Ya Ali!
 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 17;
struct Node{
	int k, p;
	Node *l, *r;
};
typedef Node* Ni;
void split(Ni t, int k, Ni& l, Ni& r){
	if(!t)
		l = r = 0;
	else if(k < t -> k)
		split(t -> l, k, l, t -> l), r = t;
	else
		split(t -> r, k, t -> r, r), l = t;
}
void insert(Ni &t, Ni it){
	if(!t)
		t = it;
	else if(it -> p < t -> p)
		insert(it -> k < t -> k ? t -> l : t -> r, it);
	else
		split(t, it -> k, it -> l, it -> r), t = it;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	
}


// Implicit treap // GSS6


// In the name of Allah.
// We're nothing and you're everything.
// Ya Ali!
 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 1e6 + 17, mod = 998244353;
int nxP(){
	static int cur = 1;
	cur = (ll) cur * 3 % mod;
	return cur;
}
struct Store{
	int pre, suf, sum, ans;
	Store (int val = -mod){
		pre = suf = sum = ans = val;
	}
	Store(int a, int b, int c, int d): pre(a), suf(b), sum(c), ans(d) {}
};
Store operator +(Store l, Store r){
	if(l.sum == -mod)
		return r;
	if(r.sum == -mod)
		return l;
	return Store(max(l.pre, l.sum + r.pre), max(r.suf, l.suf + r.sum), l.sum + r.sum, max({l.ans, r.ans, l.suf + r.pre}));
}
struct Node{
	int k, p, val;
	Store ans;
	Node *l, *r;
};
typedef Node* Ni;
int cnt(Ni i){
	return i ? i -> k : 0;
}
Store ans(Ni i){
	return i ? i -> ans : Store();
}
void upd(Ni t){
	if(!t)  return;
	t -> k = cnt(t -> l) + cnt(t -> r) + 1;
	t -> ans = ans(t -> l) + t -> val + ans(t -> r);
}
void split(Ni t, int k, Ni& l, Ni& r){
	if(!t)
		l = r = 0;
	else{
		if(k <= cnt(t -> l))
			split(t -> l, k, l, t -> l), r = t;
		else
			split(t -> r, k - 1 - cnt(t -> l), t -> r, r), l = t;
		upd(t);
	}
}
void merge(Ni &t, Ni l, Ni r){
	if(!l || !r)
		t = l ? l : r;
	else if(l -> p > r -> p)
		merge(l -> r, l -> r, r), t = l;
	else
		merge(r -> l, l, r -> l), t = r;
	upd(t);
}
Ni root;
void insert(int k, int v){
	Ni r;
	split(root, k, root, r);
	Ni nw = new Node({0, nxP(), v, v});
	merge(root, root, nw);
	merge(root, root, r);
}
void erase(int k){
	// removes kth element
	k++;
	Ni tmp, r;
	split(root, k, root, r);
	split(root, k - 1, root, tmp);
	merge(root, root, r);
}
int get(int l, int r){
	Ni qans, ri;
	split(root, r, root, ri);
	split(root, l, root, qans);
	int ret = ans(qans).ans;
	merge(root, root, qans);
	merge(root, root, ri);
	return ret;
}
void replace(int k, int v){
	erase(k);
	insert(k, v);
}
void print(Ni v, int h = 0){
	return;
	if(!v)
		return ;
	cerr << string(h * 2, ' ') << v -> k << ' ' << v -> p << ' ' << v -> val << " (" << v -> ans.pre << ' ' 
	<< v -> ans.suf << ' ' << v -> ans.sum << ' ' << v -> ans.ans << ')' << '\n';
	print(v -> l, h + 1);
	print(v -> r, h + 1);
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		insert(i, x);
	}
	print(root);
	int q;
	cin >> q;
	while(q--){
		char ty;
		cin >> ty;
		if(ty == 'Q'){
			int l, r;
			cin >> l >> r;
			cout << get(l - 1, r) << '\n';
		}
		else if(ty == 'I'){
			int p, x;
			cin >> p >> x;
			insert(p - 1, x);
		}
		else if(ty == 'R'){
			int p, x;
			cin >> p >> x;
			replace(p - 1, x);
		}
		else{
			int p;
			cin >> p;
			erase(p - 1);
		}
		print(root);		
	}
} 



// persistent treap // quera round 26 problem 7

// In the name of Allah.
// We're nothing and you're everything.
// Ya Ali!
 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 17, mod = 1e9 + 7;
const ll inf = (ll) 1e18 + 1;
mt19937 rnd(time(0));
int nxP(){
	return rnd();
	static int cur = 1;
	return cur = (ll) cur * 3 % 998244352;
}
struct Node{
	ll k;
	int p, s, val;
	Node *l, *r;
};
typedef Node* Ni;
ll cnt(Ni i){
	return i ? i -> k : 0;
}
int s(Ni i){
	return i ? i -> s : 0;	
}
void upd(Ni t){
	if(!t)  return;
	t -> k = min(inf, cnt(t -> l) + cnt(t -> r) + 1);
	t -> s = ((ll) s(t -> l) + t -> val + s(t -> r)) % mod;
}
void split(Ni t, ll k, Ni& l, Ni& r){
	if(!t)
		l = r = 0;
	else if(k <= cnt(t -> l)){
		r = new Node(*t);
		split(t -> l, k, l, r -> l);
		upd(r);
	}
	else{
		l = new Node(*t);
		split(t -> r, k - cnt(t -> l) - 1, l -> r, r);
		upd(l);
	}
}
bool cmp(Ni l, Ni r){
	return (ll) rand() * (l -> k + r -> k) < (ll) l -> k * RAND_MAX;
}
void merge(Ni &t, Ni l, Ni r){
	if(!l || !r)
		t = l ? new Node(*l) : r ? new Node(*r) : 0;
	else if(cmp(l, r))
		merge((t = new Node(*l)) -> r, l -> r, r);
	else
		merge((t = new Node(*r)) -> l, l, r -> l);
	upd(t);
}
Ni root;
int n, a[maxn];
Ni build(int l = 0, int r = n){
	if(l == r)
		return 0;
	int mid = (l + r) / 2;
	Ni nd = new Node({0, n, 0, a[mid]});
	nd -> l = build(l, mid);
	nd -> r = build(mid + 1, r);
	upd(nd);
	return nd;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	root = build();
	int q;
	cin >> q;
	while(q--){
		ll l, r, k;
		cin >> l >> r >> k;
		l--;
		Ni md, rr;
		split(root, r, root, rr);
		split(root, l, root, md);
		merge(root, root, md);
		merge(root, root, rr);
		split(root, k, root, rr);
		merge(root, root, md);
		merge(root, root, rr);
		cout << root -> s << '\n';
	}
}
