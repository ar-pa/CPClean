// In the name of God.
// We deeply belive in Ali :)
#include <bits/stdc++.h>
using namespace std;
const int mnu = 12 + 1, maxd = 31 + 1;
int mlen[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
class Time{
	int d, mo, h, mi;
public:
	int get_d(){
		return d;
	}
	int get_mo(){
		return mo;
	}
	int get_h(){
		return h;
	}
	int get_mi(){
		return mi;
	}
	Time() : mo(-1) {}
	Time(const string &s, bool type = 0){ // 0 => hh:mm, 1 => dd-mm
		d = stoi(s.substr(0, 2).c_str());
		mo = stoi(s.substr(3, 2).c_str());
		if(s.size() == 5){
			if(type == 0){
				h = d, mi = mo;
				d = mo = 0;
			}
			return ;
		}
		h = stoi(s.substr(6, 2).c_str());
		mi = stoi(s.substr(9, 2).c_str());		
	}
	Time(const int &gm, int t){
		mo = gm;
		mi = t % 60;
		t /= 60;
		h = t % 24;
		t /= 24;
		d = t + 1;
	}
	int minmo(){
		return ((d - 1) * 24 + h) * 60 + mi;
	}
	string cur() const{
		auto t = time(0);
		stringstream tmp;
		tmp << put_time(localtime(&t), "%d-%m %H:%M");
		return tmp.str();
	}
	int curm(){
		auto t = time(0);
		stringstream tmp;
		tmp << put_time(localtime(&t), "%m");
		int ret;
		tmp >> ret;
		return ret;
	}
	bool operator == (Time od){
		return mo == od.get_mo() && d == od.get_d() && h == od.h && mi == od.get_mi();
	}
	bool operator < (Time od){
		if(mo != od.get_mo())
			return mo < od.get_mo();
		if(d != od.get_d())
			return d < od.get_d();
		if(h != od.h)
			return h < od.h;
		if(mi != od.get_mi())
			return mi < od.get_mi();
		return 0;
	}
};
class Task{
	Time st, en;
	string name;
public:
	Task(Time a = Time(), Time b = Time(), string c = ""): st(a), en(b), name(c){}
	string get_name(){
		return name;
	}
	Time get_st(){
		return st;
	}
	Time get_en(){
		return en;
	}
	bool operator < (Task od){
		if(!(st == od.get_st()))
			return st < od.get_st();
		if(!(en == od.get_en()))
			return en < od.get_en();
		return 0;
	}
	bool conflict(Time od){
		return od == st || st < od && od < en;
	}
	void read(ifstream &fi){
		int sz;
		fi.read(reinterpret_cast<char*>(&sz), sizeof sz);
		name.resize(sz);
		fi.read(reinterpret_cast<char*>(name.data()), sz);
		fi.read(reinterpret_cast<char*>(&st), sizeof st);
		fi.read(reinterpret_cast<char*>(&en), sizeof en);		
	}
	void write(ofstream &fi){
		int sz = name.size();
		fi.write(reinterpret_cast<char*>(&sz), sizeof sz);
		fi.write(reinterpret_cast<char*>(name.data()), sz);
		fi.write(reinterpret_cast<char*>(&st), sizeof st);
		fi.write(reinterpret_cast<char*>(&en), sizeof en);		
	}
};
ostream& operator << (ostream &s, Time x){
	if(x.get_mo() == -1)
		s << x.cur();
	else{
		s << (x.get_d() < 10 ? "0" : "") + to_string(x.get_d());
		s << '-';
		s << (x.get_mo() < 10 ? "0" : "") + to_string(x.get_mo());
		s << ' ';
		s << (x.get_h() < 10 ? "0" : "") + to_string(x.get_h());
		s << ':';
		s << (x.get_mi() < 10 ? "0" : "") + to_string(x.get_mi());
	}
	return s;
}
ostream& operator << (ostream &s, Task x){
	s << "\"" << x.get_name() << "\" [" << x.get_st() << " - " << x.get_en() << "]";
	return s;
}
class Month{
	vector<Task> data[maxd];
public:
	vector<Task>& operator [](int i){
		return data[i];
	}
	vector<Task>* begin(){
		return data + 1;
	}
	vector<Task>* end(){
		return data + 31;
	}
};
class Year{
	Month data[mnu];
public:
	Month& operator [](int i){
		return data[i];
	}
	void read(){
		ifstream fi("d.txt", ios::binary);
		for(int i = 1; i <= mnu; i++)
			for(auto &vec : data[i]){
				int sz;
				fi.read(reinterpret_cast<char*>(&sz), sizeof sz);
				//cerr << sz << '\n';
				vec.resize(sz);
				for(auto &t : vec)
					t.read(fi);
			}
		fi.close();
	}
	void write(){
		ofstream fi("d.txt", ios::binary | ios::trunc);
		for(int i = 1; i <= mnu; i++)
			for(auto &vec : data[i]){
				int sz = vec.size();
				fi.write(reinterpret_cast<char*>(&sz), sizeof sz);
				for(auto &t : vec)
					t.write(fi);
			}
		fi.close();
	}
} dat;

int main(){
	dat.read();	
	//return 0;
	while(true){
		string q;
		cin >> q;
		cin.ignore();
		if(q == "add"){
			string title;
			{
				string tmp;
				cin >> tmp >> tmp;
				cin.ignore();
			}
			// getting title
			getline(cin, title);
			{
				string tmp;
				cin >> tmp >> tmp;
				cin.ignore();
			}
			string t;
			getline(cin, t);
			auto st = Time(t);
			{
				string tmp;
				cin >> tmp >> tmp;
				cin.ignore();
			}
			getline(cin, t);
			dat[st.get_mo()][st.get_d()].push_back(Task(st, Time(t), title));
			cin >> t;
			cin.ignore();
			cerr << "added\n";
			dat.write();
		}
		else if(q == "now")
			cout << Time().cur() << '\n';
		else if(q == "month"){
			vector<Task> v;
			for(auto d : dat[Time().curm()])
				for(auto t : d)
					v.push_back(t);
			sort(v.begin(), v.end());
			for(int i = 0; i < v.size(); i++)
				cout << "(" << i + 1 << ") " << v[i] << '\n';
		}
		else if(q == "find"){
			int len;
			{
				string t;
				getline(cin, t);
				auto st = Time(t);
				len = st.minmo() + 24 * 60;
			}
			//cerr << len << '\n';
			vector<pair<int, int> > events;
			{
				map<int, int> tmp({{0, 0}, {24 * 60 * mlen[Time().curm()] - len, 0}});
				for(auto d : dat[Time().curm()])
					for(auto t : d){
						tmp[t.get_st().minmo()]++;
						tmp[t.get_en().minmo()]--;
					}
				events.insert(events.end(), tmp.begin(), tmp.end());
			}
			int cur = 0, ptr = 0, mn = INT_MAX, cer;
			for(auto [t, tmp] : events){
				while(ptr < events.size() && events[ptr].first < t + len)
					cur += events[ptr++].second;
				if(t <= 24 * 60 * mlen[Time().curm()] - len){
					if(cur < mn)
						cer = t;
					mn = min(mn, cur);
				}
			}
			cout << "[" << Time(Time().curm(), cer) << " - " << Time(Time().curm(), cer + len) << "]" << '\n';
		}
		else if(q == "free"){
			string t;
			getline(cin, t);
			Time br = Time(t);
			for(auto &vec : dat[br.get_mo()])
				for(int i = 0; i < vec.size(); i++)
					if(vec[i].conflict(br))
						swap(vec[i--], vec.back()), vec.pop_back();
		}
		else if(q == "schedule"){
			string t;
			getline(cin, t);
			Time co = Time(t, 1);
			auto &vec = dat[co.get_mo()][co.get_d()];
			sort(vec.begin(), vec.end(), [](Task &a, Task &b){
					return a.get_en() < b.get_en();
				});
			Time ta;
			int cnt = 0;
			for(auto t : vec)
				if(ta < t.get_st() || ta == t.get_st()){
					cout << "(" << ++cnt << ") " << t << '\n';
					ta = t.get_en();
				}
		}
		else if(q == "exit")
			break;
		else{
			cerr << "Unexpected Query\n";
			return 1;
		}
	}
	
	dat.write();
}
