template<typename K, typename V>
struct offlineMap{
	vector<pair<K, V> > v;
	bool finish;
	offlineMap(): finish(0){}
	V& operator [](const K& key){
		if(finish)
			return lower_bound(v.begin(), v.end(), pair(key, V())) -> second;
		else{
			v.push_back({key, V()});
			return v.back().second;
		}
	}
	void build(){
		finish = 1;
		sort(v.begin(), v.end());
	}
};
