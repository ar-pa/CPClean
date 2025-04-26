typedef __int128 hi;

char OUTBUF[20],INBUF,*IT = OUTBUF;
istream& operator >> (istream &stream, hi &x){
    while( (INBUF = getchar()) < '0');
    for(x = INBUF - '0'; (INBUF = getchar()) >= '0'; x = (x<<3) + (x<<1) + INBUF - '0');
    return stream;
}
ostream& operator << (ostream &stream, hi x){
    do{  *IT++ = x % 10;  }  while(x /= 10);
    while(IT != OUTBUF)  putchar(*--IT + '0');
    return stream;
}

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

int sz = fread(s, 1, sizeof s, stdin);
fwrite(outbuf, 1, number of chars, stdout);

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

int _x;char OUTBUF[20],INBUF,*IT = OUTBUF;
#define in(x) while( (INBUF = getchar()) < '0');  for(_x = INBUF - '0'; (INBUF = getchar()) >= '0'; _x =  (_x << 3) + (_x << 1) + INBUF - '0');x=_x;
#define out(x) _x=x;  do{  *IT++ = _x % 10;  }  while(_x /= 10);  while(IT!=OUTBUF)  putchar(*--IT + '0');  putchar('\n');

char c, buf[maxn * 10], *it = buf + maxn * 10 - 1;  int _x;
#define in(x)  for(x = getchar() - '0'; (c = getchar()) >= '0'; x = (x << 3) + (x << 1) + c - '0');
#define write(x)  *--it = ' ';  do{  *--it = x % 10 + '0';  }  while(x /= 10);


/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */


#pragma comment(linker, "/STACK:102400000,102400000")

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

template<typename T,typename... Args>inline void in(T&x,Args&... args){in(x);if(sizeof...(args))in(args...);}

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

namespace std{
template<>struct hash<pii>{
inline size_t operator()(pii const &x)const{
return (((long long)x.X<<32)^x.Y);
}
};
}
struct fh{inline size_t operator()(int const &x)const{return x;}};

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> os;

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

template<class T>struct arr{
  T val[maxn];
  T& operator[](int idx){
    if(idx<0)
      return val[maxn-1];
    return val[idx];
  }
};

/* 88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 */

//God & me
//Damned if Amirjoon doesn't take what he wants.
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
//#define int long long
using namespace std;
template <class T, class L> bool smax(T &x,L y){  return x < y ? ( x = y, 1) : 0;  }
template <class T, class L> bool smin(T &x,L y){  return y < x ? ( x = y, 1) : 0;  }
typedef pair<int,int> pii;
const int maxn = 1e5 + 17;
