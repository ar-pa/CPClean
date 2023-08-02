/// builds the segment tree
void build() {
	copy(a, a + n, seg + n);
	for (int i = n - 1; i; i--)
		seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
}

/// changes value of i'th element to x
void update(int i, int x) {
	for (seg[i += n] = x; i >>= 1;)
		seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
}

/// returns the maximum value of segment [l, r)
int get(int l, int r) {
	int ans = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1)
			ans = max(ans, seg[l++]);
		if (r & 1)
			ans = max(ans, seg[--r]);
	}
	return ans;
}
