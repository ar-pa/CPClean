const int MAX_N = 5e5 + 14;

struct Lazy;

struct Node {
	ll sum = 0;
	array<int, 2> cnt{};
	int last_update = 0;

	ll sum_at(int i) const {
		return sum + cnt[1] * ll(i - last_update);
	}

	Node operator+(const Node &o) {
		int last = max(last_update, o.last_update);
		return {sum_at(last) + o.sum_at(last), {cnt[0] + o.cnt[0], cnt[1] + o.cnt[1]}, last};
	}

	Node operator+(const Lazy &lazy);
} tree[1 << 20];

struct Lazy {
	int first_time = -1;
	int cnt[2]{};
	bool flip{};

	Lazy operator+(Lazy o) {
		if (first_time == -1)
			return o;
		o.cnt[1] += o.first_time - cnt[0] - cnt[1] - first_time;
		if (flip)
			swap(o.cnt[0], o.cnt[1]);
		return {first_time, {cnt[0] + o.cnt[0], cnt[1] + o.cnt[1]}, flip ^ o.flip};
	}
} lazy[1 << 20];

Node Node::operator+(const Lazy &lazy) {
	return {sum_at(lazy.first_time) + (ll) cnt[0] * lazy.cnt[0] + (ll) cnt[1] * lazy.cnt[1],
			lazy.flip ? array{cnt[1], cnt[0]} : cnt, lazy.first_time + lazy.cnt[0] + lazy.cnt[1]};
}

int n;

void build(int l = 0, int r = n, int id = 1) {
	if (l + 1 == r) {
		tree[id].cnt[0] = 1;
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, id * 2);
	build(mid, r, id * 2 + 1);
	tree[id] = tree[id * 2] + tree[id * 2 + 1];
}

void shift(int id) {
	if (lazy[id].first_time == -1)
		return;
	lazy[id * 2] = lazy[id * 2] + lazy[id];
	tree[id * 2] = tree[id * 2] + lazy[id];
	lazy[id * 2 + 1] = lazy[id * 2 + 1] + lazy[id];
	tree[id * 2 + 1] = tree[id * 2 + 1] + lazy[id];
	lazy[id] = Lazy();
}

void update(int s, int e, const Lazy &q, int l = 0, int r = n, int id = 1) {
	if (s <= l && r <= e) {
		tree[id] = tree[id] + q;
		lazy[id] = lazy[id] + q;
		return;
	}
	if (e <= l || r <= s)
		return;
	shift(id);
	int mid = (l + r) / 2;
	update(s, e, q, l, mid, id * 2);
	update(s, e, q, mid, r, id * 2 + 1);
	tree[id] = tree[id * 2] + tree[id * 2 + 1];
}

ll get(int s, int e, int time, int l = 0, int r = n, int id = 1) {
	if (s <= l && r <= e)
		return tree[id].sum_at(time);
	if (e <= l || r <= s)
		return 0;
	shift(id);
	int mid = (l + r) / 2;
	return get(s, e, time, l, mid, id * 2) + get(s, e, time, mid, r, id * 2 + 1);
}
 