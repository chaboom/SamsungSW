#include <iostream>
#include <string>
using namespace std;

string origin;
int ans;
bool visit[1000000][11];

void init() {
	for (int i = 0; i < 1000000; i++) {
		for (int j = 0; j < 10; j++) {
			visit[i][j] = false;
		}
	}
}
int mul(int cnt) {
	int n = 1;
	for (int i = 0; i < cnt; i++) {
		n *= 10;
	}
	return n;
}
int stringtoint(string s) {
	int n = 0, cnt = 0;
	for (int i = s.length()-1; i >= 0; i--) {
		n += (s[i] - '0') * mul(cnt);
		cnt++;
	}
	return n;
}
string swap(string s, int i, int j) {
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
	return s;
}
void go(string s, int N) {
	int n = stringtoint(s);
	visit[n][N] = true;
	if (N == 0) {		
		if (ans < n) ans = n;
		return;
	}
	for (int i = 0; i < s.length(); i++) {
		for (int j = i + 1; j < s.length(); j++) {
			string next = swap(s, i, j);
			if(!visit[stringtoint(next)][N-1])
				go(next, N - 1);
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N;
		cin >> origin;
		cin >> N;
    
		ans = 0;
		init();
		go(origin, N);
		
		cout << "#" << tc << " " << ans << endl;
	}	
	return 0;
}
