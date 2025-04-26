const int MOD = 1e9 + 7;

struct ModInt {
    int x;

    ModInt(ll x = 0) : x(((x % MOD) + MOD) % MOD) {}

    explicit operator int() const {
        return x;
    }

    bool operator==(const ModInt &rhs) const {
        return x == rhs.x;
    }

    bool operator!=(const ModInt &rhs) const {
        return !(rhs == *this);
    }

    friend ModInt operator+(const ModInt &l, const ModInt &r) {
        return l.x + r.x;
    }

    ModInt &operator+=(const ModInt &o) {
        return *this = *this + o;
    }

    friend ModInt operator-(const ModInt &l, const ModInt &r) {
        return l.x - r.x;
    }

    ModInt operator-() const {
        return -x;
    }

    ModInt &operator-=(const ModInt &o) {
        return *this = *this - o;
    }

    friend ModInt operator*(const ModInt &l, const ModInt &r) {
        return (ll) l.x * r.x;
    }

    ModInt &operator*=(const ModInt &o) {
        return *this = *this * o;
    }

    ModInt pow(ll b) const {
        ModInt ans = 1;
        ModInt a = *this;
        for (; b; b >>= 1, a = a * a)
            if (b & 1)
                ans *= a;
        return ans;
    }

    ModInt rev() const {
        return pow(MOD - 2);
    }

    friend ModInt operator/(const ModInt &l, const ModInt &r) {
        return l * r.rev();
    }

    ModInt &operator/=(const ModInt &o) {
        return *this = *this / o;
    }

    friend ostream &operator<<(ostream &os, const ModInt &anInt) {
        os << anInt.x;
        return os;
    }
};

ModInt fac[MAX_N] = {1}, rfac[MAX_N] = {1};

ModInt c(int n, int r) {
    return n < r || r < 0 ? 0 : fac[n] * rfac[r] * rfac[n - r];
}

void prep() {
    for (int i = 1; i < MAX_N; ++i)
        fac[i] = fac[i - 1] * i;
    rfac[MAX_N - 1] = fac[MAX_N - 1].rev();
    for (int i = MAX_N - 2; i >= 0; --i)
        rfac[i] = (i + 1) * rfac[i + 1];
}
