struct Gauss{
	int a[lg];
	Gauss(){
		memset(a, 0, sizeof a);
	}
	void add(int x){
		for(int i = lg - 1; i >= 0; i--)
			if(x >> i & 1)
				if(a[i])
					x ^= a[i];
				else{
					a[i] = x;
					break;
				}
	}
	int mx(){
		int ans = 0;
		for(int i = lg - 1; i >= 0; i--)
			ans = max(ans, ans ^ a[i]);
		return ans;
	}
};



template<typename T, size_t Size>
struct GaussSolver {
    array<T, Size + 1> matrix[Size];
    array<T, Size> solve();
};

template<typename T, size_t Size>
int pivot(const array<T, Size> &r) {
    int ans = 0;
    while (ans < Size and r[ans] == 0)
        ans++;
    return ans;
}

template<typename T, size_t Size>
array<T, Size> operator+=(array<T, Size> &a, const array<T, Size> &b) {
    for (int i = 0; i < Size; ++i)
        a[i] += b[i];
    return a;
}

template<typename T, size_t Size>
array<T, Size> operator*(const array<T, Size> &a, T b) {
    array<T, Size> c;
    for (int i = 0; i < Size; ++i)
        c[i] = a[i] * b;
    return c;
}


template<typename T, size_t Size>
array<T, Size> GaussSolver<T, Size>::solve() {
    for (int i = 0; i < Size; i++) {
        int p = pivot(matrix[i]);
        assert(p <= Size);
        for (int j = 0; j < Size; j++)
            if (j != i and matrix[j][p] != 0)
                matrix[j] += matrix[i] * (-matrix[j][p] / matrix[i][p]);
    }
    array<T, Size> ans;
    for (int i = 0; i < Size; i++) {
        int p = pivot(matrix[i]);
        ans[p] = matrix[i][Size] / matrix[i][p];
    }
    return ans;
}
