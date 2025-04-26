//God & me // ya mahdi adrekni '-|
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+12;
int n;
bool ok(int x){
  return x*x<=n;
}
int f(int n){
  int l=0,r=n+1;
  while(r-l>1){
    int mid=(l+r)>>1;
    if(ok(mid))
      l=mid;
    else
      r=mid;
  }
  return l;
}
main(){
  cin>>n;
  cout<<f(n)<<endl;
  return 0;
}
