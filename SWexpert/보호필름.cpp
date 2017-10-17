#include<iostream>
#include<vector>
using namespace std;

int D, W, K;

int min(int a, int b) {
	if (a < b) return a;
	else return b;
}

bool check(vector<vector<int> >map) {
	bool test = true;
	for (int j = 0; j < W; j++) {
		bool pass = false;
		for (int i = 0; i < D;) {
			int cnt = 0, k = i;
			while (k < D && (map[i][j] == map[k][j])) {
				k++;
				cnt++;
			}
			if (cnt >= K) {
				pass = true;
				break;
			}
			i += cnt;
		}
		test &= pass;
	}
	return test;
}

int injection(vector<vector<int> > map, int i, int level) {
	if (level == K) return level;
	if (i >= D) return i;
	vector<vector<int> > temp(D, vector<int>(W, 0));
	temp = map;
    
	for (int a = 0; a < D; a++) {
		if (a == i) continue;
		map[a] = vector<int>(W, 0);
		if (check(map)) return level;
		map[a] = vector<int>(W, 1);
		if (check(map)) return level;
		map = temp;
	}
	map[i] = vector<int>(W, 0);
	int A = injection(map, i + 1, level + 1);
	map[i] = vector<int>(W, 1);
	int B = injection(map, i + 1, level + 1);

	return min(A, B);
}
int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> D >> W >> K;
		vector<vector<int> > map(D, vector<int>(W, 0));
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
			}
		}
		if (check(map)) { cout << "#" << tc << " 0" << endl; continue; }
		
        int ans = K;
		for (int i = 0; i < D; i++) {
			int result = injection(map, i, 1);
			if (ans > result) ans = result;
		}
		cout << "#" << tc << " " << ans << endl;
	}
	return 0;
}
