// God & me
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
#define int long long
using namespace std;
template <class T, class L> bool smax(T &x,L y){  return x < y ? (x = y, 1) : 0;  }
template <class T, class L> bool smin(T &x,L y){  return y < x ? (x = y, 1) : 0;  }
typedef pair<int, int> pii;

const int maxn = 1e5 + 17, base = maxn + 17, mod = 1e9 + 17;
int n, hp[maxn], hs[maxn], po[maxn];
string s, p;
void make(string &s, int *h){
    for(int i = 1; i <= s.size(); i++)
	h[i] = (h[i - 1] * base + s[i - 1]) % mod;
    // h[i] = s[i - 1] * base ^ 0 + s[i - 2] * base ^ 1 + s[i - 3] * base ^ 2 + s[i - 4] * base ^ 3 + ...
}
int get(int *h, int l, int r){
    return (h[r] - h[l] * po[r - l] % mod + mod) % mod;
    // h[r] = s[r - 1] * base ^ 0 + s[r - 2] * base ^ 1 + ... + s[l] * base ^ (r - l + 1) + s[l - 1] * base ^ (r - l) + s[l - 2] * base ^ (r - l - 1) + ...
    // h[l] = s[l - 1] * base ^ 0 + s[l - 2] * base ^ 1 + s[l - 3] * base ^ 2 + s[l - 4] * base ^ 3 + ...
    // h[l] * po[r - l] = s[l - 1] * base ^ (r - l) + s[l - 2] * base ^ (r - l + 1) + s[l - 3] * base ^ (r - l + 2) + s[l - 4] * base ^ (r - l + 3) + ...
    // => h[r] - h[l] * po[r - l] = s[r - 1] * base ^ 0 + s[r - 2] * base ^ 1 + ... + s[l] * base ^ (r - l + 1)
}
void init(){
    *po = 1;
    for(int i = 1; i < maxn; i++)  po[i] = po[i - 1] * base % mod;	
    make(s, hs);
    make(p, hp);
}
main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> s >> p;
    init();
    for(int i = p.size(); i <= s.size(); i++)
	if(hp[p.size()] == get(hs, i - p.size(), i))
	    cout << "match at [" << i - p.size() << ", " << i - 1 << ']' << '\n';
    return 0;
}
