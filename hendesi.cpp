long double ang(long double x,long double y){
  return atanl((long double)(y)/(x))/3.14159265358979323851*180+(x<0)*180+(atanl((long double)(y)/(x))/3.14159265358979323851*180+(x<0)*180<0)*360;
}
long long cross(pair<int,int>a,pair<int,int>b,pair<int,int>c){
  return 1ll*(b.X-a.X)*(c.Y-a.Y)-1ll*(b.Y-a.Y)*(c.X-a.X);
}
long long cross(int a,int b,int c){
  return 1ll*(x[b]-x[a])*(y[c]-y[a])-1ll*(y[b]-y[a])*(x[c]-x[a]);
}
struct lab{
  long double a,b;
};
struct labc{
  long double a,b,c;
};
bool inter(labc a,labc b,lab &ans){
	  
  return 1;
}
