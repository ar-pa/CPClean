//God & me 
//I have agreed about this: "God can do anything" :-"
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
using namespace std;
template<class T,class L>bool smax(T&x,L y){return x<y?(x=y,1):0;}template<class T,class L>bool smin(T&x,L y){return x>y?(x=y,1):0;}
typedef pair<int,int> pii;
const int maxn=2e5+17,sq=448,maxv=1e6+17;
struct Q{
  int l,r,idx;
}q[maxn];
int n,a[maxn],qn,cnt[maxv];
long long cur,ans[maxn];
void add(int x,int v){
  x=a[x];
  cur-=(long long)cnt[x]*cnt[x]*x;
  cnt[x]+=v;
  cur+=(long long)cnt[x]*cnt[x]*x;
}
main(){
  in(n);in(qn);
  for(int i=0;i<n;i++){
    in(a[i]);
  }
  for(int i=0;i<qn;i++){
    in(q[i].l);in(q[i].r);q[i].l--,q[i].idx=i;
  }
  sort(q,q+qn,[](Q& a,Q& b){
      if(a.l/sq!=b.l/sq)
	return a.l<b.l;
      return bool((a.r<b.r)^((a.l/sq)&1));
    });
  int l=0,r=0;
  for(int i=0;i<qn;i++){
    int nxl=q[i].l,nxr=q[i].r;
    while(r<nxr)
      add(r++,1);
    while(l>nxl)
      add(--l,1);
    while(r>nxr)
      add(--r,-1);
    while(l<nxl)
      add(l++,-1);
    ans[q[i].idx]=cur;
  }
  for(int i=0;i<qn;i++){
    out(ans[i]);
  }
  return 0;
}

