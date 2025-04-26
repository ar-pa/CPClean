#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n,t,res;
vector<vector<int> >a;
void bs(int st,int en,int k){
  if(st==en){
    if(a[st][a[st].size()-1]>k)
      res=min(res,(st+en+1)/2);
  }
  else if(st+1==en){
    if(a[st][a[st].size()-1]>k)
      res=min(res,(st+en+1)/2);
    if(a[st+1][a[st+1].size()-1]>k)
      res=min(res,(st+1+en+1)/2);
  }
  else{
    if(a[(st+en+1)/2][a[(st+en+1)/2].size()-1]<=k)
      bs((st+en+1)/2+1,en,k);
    else
      res=min(res,(st+en+1)/2),bs(st,(st+en+1)/2-1,k);
  }
}
int main(){
  cin>>n;
  cin>>t;
  a.resize(1);
  a[0].push_back(t);
  for(int i=1;i<n;i++){
    cin>>t;
    res=10000;
    bs(0,a.size()-1,t);
    if(res==10000){
      a.resize(a.size()+1);
      a[a.size()-1].push_back(t);
    }      
    else
      a[res].push_back(t);
  }
  /*for(int i=0;i<a.size();i++){
    for(int j=0;j<a[i].size();j++)
      cout<<a[i][j]<<" ";
    cout<<endl;
    }*/
  int maxx=0;
  for(auto &v:a)
    maxx=max(a.size(),maxx);
  cout<<maxx<<'\n';
  return 0;
}
