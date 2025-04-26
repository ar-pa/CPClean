//God & me
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
#define rank khtdhg
#define left saduh
#define right sfsfd
using namespace std;
const int maxn=1e5+12,lg=20;
int n,r[lg][maxn],sz,rank[maxn],dp[maxn],left[maxn],right[maxn];
pair<pair<int,int>,int>q[maxn*lg];
pair<int,int>a[maxn];
int lcp(int i,int j){
  int ans=0;
  for(int k=lg-1;k>=0 && i<n && j<n;k--)
    if(r[k][i]==r[k][j])
      i+=(1<<k),j+=(1<<k),ans|=(1<<k);
  return ans;
}
string s;
int main(){
  cin>>s,n=s.length();
  for(int i=0;i<n;i++)
    r[0][i]=s[i];
  for(int i=1;i<lg;i++){
    for(int j=0;j<n;j++)
      if(j+(1<<(i-1))>=n)
	q[j]={{r[i-1][j],-1},j};
      else
	q[j]={{r[i-1][j],r[i-1][j+(1<<(i-1))]},j};
    sort(q,q+n);
    for(int j=1;j<n;j++)
      r[i][q[j].Y]=(q[j].X==q[j-1].X?r[i][q[j-1].Y]:j);
  }
  for(int i=0;i<n;i++)
    a[i]={r[lg-1][i],i};
  sort(a,a+n);
  for(int i=0;i<n;i++)
    rank[i]=a[i].Y;
  //for(int i=0;i<n;i++)cout<<rank[i]<<' ';cout<<endl;
  for(int i=0;i<n-1;i++)
    dp[i]=lcp(rank[i],rank[i+1]);
  stack<pair<int,int> >st;
  st.push({-1e9,-1});
  for(int i=0;i<n-1;i++){
    while(st.top().X>dp[i])st.pop();
    left[i]=st.top().Y;
    st.push({dp[i],i});
  }
  st=stack<pair<int,int> >();
  st.push({-1e9,n-1});
  for(int i=n-2;i>=0;i--){
    while(st.top().X>=dp[i])st.pop();
    right[i]=st.top().Y;
    st.push({dp[i],i});
  }
  long long ans=0;
  for(int i=0;i<n-1;i++)
    ans+=1ll*(right[i]-i)*(i-left[i])*dp[i];
  cout<<ans+1LL*n*(n+1)/2<<'\n';
  return 0;
}
