#include <iostream>
#include <vector>
using namespace std;
vector<int> heap;
int n,t;
void heap_down(int a){
  if(2*a>heap.size()-1)
    return ;
  if(2*a==heap.size()-1){
    if(heap[a]<heap[2*a])
      swap(heap[a],heap[2*a]);
  }
  else{
      bool maxb=0;
      if(heap[a*2]<heap[a*2+1])
	maxb=1;
      if(heap[a*2+maxb]>heap[a]){
	swap(heap[a*2+maxb],heap[a]);
	heap_down(a*2+maxb);
      }
    }
}
void heap_up(int a){
  if(a==1)return ;
  if(heap[a]>heap[a/2]){
    swap(heap[a],heap[a/2]);
    heap_up(a/2);
  }
}
void add(int a){
  heap.push_back(a);
  heap_up(heap.size()-1);
}
int pop(){
  int cn=heap[1];
  heap[1]=heap[heap.size()-1];
  heap.pop_back();
  heap_down(1);
  return cn;
}
vector<int>sort(){
  vector<int>res;
  while(heap.size()>1)
    res.push_back(pop());
  return res;
}
void make_heap(){
  for(int i=heap.size()-1;i>0;i--)
    heap_down(i);
}
int main(){
  heap.push_back(0);
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>t;
    add(t);
  }
  cout<<endl;
  for(int i=1;i<heap.size();i++)
    cout<<heap[i]<<" ";
  cout<<endl;
  cin>>n;
  for(int i=0;i<n;i++){
    pop();
  }
  cout<<endl;
  for(int i=1;i<heap.size();i++)
    cout<<heap[i]<<" ";
  cout<<endl;

  return 0;
}
