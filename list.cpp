#include <iostream>
using namespace std;
struct node{
  char data;
  node *prev,*next;
};
node *gaurd;
void print (){
  for(node *i=gaurd->next;;i=i->next){
    cout<<i->data;
    if(i->next=gaurd)
      break;
  }
}
void rem(node *p){
  p->prev->next=p->next;
  p->next->prev=p->prev;
}
void add(node *p,char x){
  node *t=new node;
  t->data=x;
  t->next=p->next;
  t->prev=p;
  p->next=t;
  t->next->prev=t;
}
int main(){
  gaurd=new node;
  gaurd->next=gaurd->prev=gaurd;
  cin>>n;
  node *cur=gaurd;
  while(n--){
    char c;
    cin>>c;
    if(c=='L'){
      if(cur!=gaurd)
	cur=cur->prev;
    }
    else if(c=='R'){
      if(cur->next!=gaurd)
	cur=cur->next;
    }
    else if(c=='B'){
      if(cur!=gaurd){
	rem(cur);
	cur=cur->prev;
      }
    }
    else{
      add(cur,c);
      cur=cur->next;
    }
  }
  print();
  return 0;
}


