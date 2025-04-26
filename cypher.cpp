// God & me
// le me play...
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 17;
class Ot{
	string key, ckey;
public:
	Ot(string K) : key(K), ckey(K) {  }
	string decode(string s){
		assert(s.size() <= key.size());
		for(int i = 0; i < s.size(); i++)
			s[i] = (s[i] - 32 - key[i] + 126 - 32 + 2) % (126 - 32 + 2) + 32;
		key.erase(0, s.size());
		return s;
	}
	string encode(string s){
		assert(s.size() <= ckey.size());
		for(int i = 0; i < s.size(); i++)
			s[i] = (s[i] - 32 + ckey[i]) % (126 - 32 + 2) + 32;
		ckey.erase(0, s.size());
		return s;
	}
};
int main(){
	string s;
	cin >> s;
	cin.ignore();
	Ot cy(s);
	while(true){
		getline(cin, s);
		if(s == "" || s == "exit")
			return 0;
		bool type = s[0] == 'e';
		s = s.substr(7);
		cout << (type ? cy.encode(s) : cy.decode(s)) << '\n';
	}
}
