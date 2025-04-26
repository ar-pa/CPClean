template<class cmp> struct LS{
    vector<int> v;
    vector<pair<int, int> > his;
    void add(int x){
	int p = upper_bound(v.begin(), v.end(), x, cmp()) - v.begin();
	if(p == v.size()){
	    his.push_back({-1, 0});
	    v.push_back(x);
	}
	else{
	    his.push_back({p, v[p]});
	    v[p] = x;
	}
    }
    void swap(LS<cmp> &od){  od.v.swap(v);  }
    void merge(LS<cmp> &od){
	if(od.v.size() > v.size())
	    v.swap(od.v);
	for(int i = 0; i < od.v.size(); i++)
	    if(cmp()(od.v[i], v[i]))  v[i] = od.v[i];
    }
    void undo(){
	assert(his.size());
	if(his.back().first == -1)
	    v.pop_back();
	else
	    v[his.back().first] = his.back().second;
	his.pop_back();
    }
};
typedef LS<less<int> > Lis;
typedef LS<greater<int> > Lds;
