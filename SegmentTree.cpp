const int maxn = 1e5 + 12;
int n, s[maxn << 2], a[maxn], q;

void up(int id) {
	s[id] = s[id << 1] + s[id << 1 | 1];
}

void build(int l = 0, int r = n, int id = 1) {
	if (r - l < 2) {
		s[id] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, id << 1), build(mid, r, id << 1 | 1);
	up(id);
}

void add(int p, int v, int l = 0, int r = n, int id = 1) {
	if (r - l < 2) {
		s[id] += v;
		return;
	}
	int mid = (l + r) >> 1;
	if (p < mid)
		add(p, v, l, mid, id << 1);
	else
		add(p, v, mid, r, id << 1 | 1);
	up(id);
}

int sum(int st, int en, int l = 0, int r = n, int id = 1) {
	if (st <= l && r <= en)
		return s[id];
	if (en <= l || r <= st)
		return 0;
	int mid = (l + r) >> 1;
	return sum(st, en, l, mid, id << 1) + sum(st, en, mid, r, id << 1 | 1);
}