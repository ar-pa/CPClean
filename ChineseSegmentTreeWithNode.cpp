struct Node {
	int pre, sum;

	Node(int pre, int sum) : pre(pre), sum(sum) {}

	Node(int x = 0) {
		pre = max(0, sum = x);
	}
};

Node mrg(Node l, Node r) {
	return {max(l.pre, l.sum + r.pre), l.sum + r.sum};
}

template<typename Node>
class SegmentTree {
	function<Node(Node, Node)> merge;
	Node* data;
	size_t size;
public:
	template<typename T>
	SegmentTree(T a, int n, function<Node(Node, Node)> merge): merge(merge) {
		size = 1 << 32 - __builtin_clz(n - 1);
		data = new Node[size * 2];
		for (int i = 0; i < n; ++i)
			data[i + size] = a[i];
		for (int i = size - 1; i > 0; i--)
			data[i] = merge(data[i << 1], data[i << 1 | 1]);
	}

	void upd(int p, const Node &v) {
		for (data[p += size] = v; p >>= 1;)
			data[p] = merge(data[p << 1], data[p << 1 | 1]);
	}

	Node get(int l, int r) {
		Node lef, ri;
		for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
			if (l & 1)
				lef = merge(lef, data[l++]);
			if (r & 1)
				ri = merge(data[--r], ri);
		}
		return merge(lef, ri);
	}

	virtual ~SegmentTree() {
		delete[] data;
	}
};
