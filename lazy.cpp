#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5;
int n,a[maxn],q,s[maxn<<2],lazy[maxn<<2];
void build(int id=1,int l=0,int r=n){
  if(r-l<2){
    s[id]=a[l];
    return;
  }
  int mid=(l+r)>>1;
  build(id<<1,l,mid);
  build(id<<1|1,mid,r);
  s[id]=s[id<<1]+s[id<<1|1];
}
void up(int id,int l,int r,int x){
  lazy[id]+=x;
  s[id]+=(r-l)*x;
}
void shift(int id,int l,int r){
  int mid=(l+r)>>1;
  up(id<<1,l,mid,lazy[id]);
  up(id<<1|1,mid,r,lazy[id]);
  lazy[id]=0;
}
void add(int st,int en,int v,int id=1,int l=0,int r=n){
  if(en<=l || r<=st)
    return;
  if(st<=l && r<=en){
    up(id,l,r,v);
    return;
  }
  shift(id,l,r);
  int mid=(l+r)>>1;
  add(st,en,v,id<<1,l,mid);
  add(st,en,v,id<<1|1,mid,r);
  s[id]=s[id<<1]+s[id<<1|1];
}
int sum(int st,int en,int id=1,int l=0,int r=n){
  if(en<=l || r<=st)
    return 0;
  if(st<=l && r<=en)
    return s[id];
  shift(id,l,r);
  int mid=(l+r)>>1;
  return sum(st,en,id<<1,l,mid)+sum(st,en,id<<1|1,mid,r);
}
int main(){
  cin>>n>>q;
  for(int i=0;i<n;i++)
    cin>>a[i];
  build();
  while(q--){
    int t,l,r,v;
    cin>>t>>l>>r,l--;
    if(t){
      cout<<sum(l,r)<<endl;
    }
    else{
      cin>>v;
      add(l,r,v);
    }
  }
  return 0;
}
