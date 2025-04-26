const int maxmat = 5e2 + 17, mod = 1e9 + 7;
struct mat{
    int a[maxmat][maxmat];
    mat(bool v = 0){
	memset(a, 0, sizeof a);
	for(int i = 0; i < maxmat; i++)  a[i][i] = v;
    }
    int* operator[](int idx){
	return a[idx];
    }
};
int fix(int x){  return x >= mod ? x - mod : x;  }
mat operator *(mat &a, mat &b){
    mat ans;
    for(int i = 0; i < maxmat; i++)
	for(int k = 0; k < maxmat; k++)
	    for(int j = 0; j < maxmat; j++)
		ans[i][j] = (ans[i][j] + (long long) a[i][k] * b[k][j]) % mod;
    return ans;
}
mat operator +(mat &a, mat &b){
    mat ans;
    for(int i = 0; i < maxmat; i++)
	for(int j = 0; j < maxmat; j++){
	    ans[i][j] = fix(a[i][j] + b[i][j]);
	}
    return ans;
}
mat operator ^(mat a, int b){
    mat ans(1);
    for( ; b; b >>= 1, a = a * a)
	if(b & 1)
	    ans = ans * a;
    return ans;
}

