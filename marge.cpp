#include <iostream>
#include <vector>
using namespace std;
vector<int>so(vector<int>a){
  if(a.size()==1)
    return a;
  if(a.size()==2){
    if(a[0]>a[1])
      swap(a[0],a[1]);
    return a;
  }
  vector<int>f,s,l;
  //sorting
  for(int i=0;i<a.size()/2;i++)
    f.push_back(a[i]);
  f=so(f);
  for(int i=a.size()/2;i<a.size();i++)
    s.push_back(a[i]);
  s=so(s);
  //marging
  int pf=0,ps=0;
  while(l.size()<a.size()){
    if(f[pf]<s[ps]){
      l.push_back(f[pf]);
	pf++;
    }
    else{
      l.push_back(s[ps]);
	ps++;
    }
    if(pf==f.size() || ps==s.size())
      break;
  }
  while(ps<s.size())
    l.push_back(s[ps]),ps++;
  while(pf<f.size())
    l.push_back(f[pf]),pf++;

  return l;
}
int main(){
  vector<int>v;
  int n;
  cin>>n;
  v.resize(n);
  for(int i=0;i<n;i++)
    cin>>v[i];
  v=so(v);
  for(int i=0;i<n;i++)
    cout<<v[i]<<" ";
  cout<<endl;
}

