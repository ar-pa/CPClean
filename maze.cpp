#include <iostream>
#include <vector>
#define X first
#define Y second
using namespace std;
char map[500][500];
int n,m;
vector<pair<int,int> >e[500][500];
pair<int,int>mu;
pair<int,int>c;
bool mark[500][500];
bool dfs(pair<int,int>v){
  if(v==c)return 1;
  for(int i=0;i<e[v.X][v.Y].size();i++){
    if(mark[e[v.X][v.Y][i].X][e[v.X][v.Y][i].Y]==0){
      mark[e[v.X][v.Y][i].X][e[v.X][v.Y][i].Y]=1;
      if(dfs(make_pair(e[v.X][v.Y][i].X,e[v.X][v.Y][i].Y))==1 && v!=mu){
	map[v.X][v.Y]='*';
	return 1;
      }
    }
  }
}
int main(){
  cin>>n>>m;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      cin>>map[i][j];
      if(map[i][j]=='m')
	mu=make_pair(i,j);
      else if(map[i][j]=='c')
	c=make_pair(i,j);
    }

  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      if(map[i][j]!='#'){
	if(i!=0 && map[i-1][j]!='#'){
	  e[i][j].push_back(make_pair(i-1,j));
	  e[i-1][j].push_back(make_pair(i,j));
	}
	if(j!=0 && map[i][j-1]!='#'){
	  e[i][j].push_back(make_pair(i,j-1));
	  e[i][j-1].push_back(make_pair(i,j));
	}
	if(i!=n-1 && map[i+1][j]!='#'){
	  e[i][j].push_back(make_pair(i+1,j));
	  e[i+1][j].push_back(make_pair(i,j));
	}
	if(j!=n-1 && map[i][j+1]!='#'){
	  e[i][j].push_back(make_pair(i,j+1));
	  e[i][j+1].push_back(make_pair(i,j));
	}
      }
    }

  mark[mu.X][mu.Y]=1;
  
  dfs(mu);
  
  for(int i=0;i<n;i++,cout<<endl)
    for(int j=0;j<m;j++)
      cout<<map[i][j];
  return 0;
}
