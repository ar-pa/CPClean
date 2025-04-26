//God & me // ya mahdi adrekni '-|
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+12,mod=1e9+7;
long long n,m,a[maxn],z[maxn],ans=1;
string s;
int main(){
  ios::sync_with_stdio(0);
  cin>>n>>m>>s;
  if(!m){
    for(int i=0;i<n;i++)
      ans*=26,ans%=mod;
    cout<<ans<<'\n';
    return 0;
  }
  int l=0,r=0;
  for(int i=1;i<s.length();i++)
    if(r<i){
      r=l=i;
      while(r<s.length() && s[r-i]==s[r])r++;
      z[i]=r-l;
    }
    else if(z[i-l]<r-i)
      z[i]=z[i-l];
    else{
      l=i;
      while(r<s.length() && s[r-i]==s[r])r++;
      z[i]=r-l;
    } 
  /*for(int i=0;i<s.size();i++)
    cout<<z[i]<<' ';
    cout<<'\n';*/
  cin>>a[0],a[0]--;
  for(int i=1;i<m;i++){
    cin>>a[i],a[i]--;
    if(z[a[i]-a[i-1]]<a[i-1]+s.length()-a[i])
      cout<<"0\n",exit(0);
  }
  //cout<<":)\n";
  int p=0;
  for(int i=0;i<a[0];i++)
    ans*=26,ans%=mod;
  for(int i=0;i<n;i++)
    if(p<m-1 && a[p+1]==i)
      p++;
    else if(a[p]+s.length()<=i)
      ans*=26,ans%=mod;
  cout<<ans<<'\n';
  return 0;
}
