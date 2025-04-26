//God & me // ya mahD adrekni 
#include <bits/stdc++.h>
using namespace std;
const int mh=30;
bool stak[mh+1];
int sz;

void insert(string &s){
  int pos=0;
  for(auto &c:s)
    c-='a',pos=t[pos][c]?t[pos][c]:t[pos][c]=sz++;
}


struct trie{
  int tr[1000012][2],size=1;
  inline void insert(int x){
    for(int i=0;i<=mh;i++)
      stak[sz++]=x&1,x>>=1;
    int pos=0;
    while(sz--){
      if(!tr[pos][stak[sz]])
	tr[pos][stak[sz]]=size++;
      pos=tr[pos][stak[sz]];
    }
  }
  inline bool find(int x){
    for(int i=0;i<=mh;i++)
      stak[sz++]=x&1,x>>=1;
    int pos=0;
    while(sz--){
      if(!tr[pos][stak[sz]])
	return sz=0;
      pos=tr[pos][stak[sz]];
    }
    return true;
  }
};
trie a;
int q,x;
int main(){
  cin>>q;
  while(q--){
    cin>>x;
    cout<<a.find(x)<<endl;
    a.insert(x);
  }
  return 0;
}
//be omide khoda!
