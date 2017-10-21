#include <iostream>
#include <queue>

using namespace std;

bool check(int *t, int size) {
	bool end = true;
	for (int k = 1; k <= size; k++) {
		if (t[k] > 0) return false;
	}
	return end;
}
bool check(pair<int,int> *a, int size) {
	bool end = true;
	for (int k = 1; k <= size; k++) {
		if (a[k].first > 0) return false;
	}
	return end;
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N, M, K, A, B, ans = 0, t[1001];
		int a[10], b[10];
		pair<int,int> astate[10], bstate[10];
		pair<int, int> d[1001];
		queue<int> waitA, waitB;

		cin >> N >> M >> K >> A >> B;

		for (int i = 1; i <= N; i++) {
			cin >> a[i];
			astate[i].first = 0;
			astate[i].second = 0;
		}
		for (int j = 1; j <= M; j++) {
			cin >> b[j];
			bstate[j].first = 0;
			bstate[j].second = 0;
		}
		for (int k = 1; k <= K; k++) {
			cin >> t[k];
		}

		int time = t[1];
		while (true) {		
			for (int k = 1; k <= K; k++) {
				if (t[k] == time) {
					waitA.push(k);
					t[k] = 0;
				}
			}			
			for (int i = 1; i <= N; i++) {
				if (!waitA.empty() && astate[i].first == 0) {
					int cnum = waitA.front();
					astate[i].first = cnum;
					astate[i].second = 1;
					d[cnum].first = i;
					waitA.pop();
				}				
			}		
			for (int j = 1; j <= M; j++) {
				if (!waitB.empty() && bstate[j].first == 0) {
					int cnum = waitB.front();
					bstate[j].first = cnum;
					bstate[j].second = 1;
					d[cnum].second = j;
					waitB.pop();
				}				
			}

			for (int i = 1; i <= N; i++) {
				if (astate[i].second == a[i]) {
					waitB.push(astate[i].first);
					astate[i].first = 0;
					astate[i].second = 0;
				}
			}
			for (int j = 1; j <= M; j++) {
				if (bstate[j].second == b[j]) {
					bstate[j].first = 0;
					bstate[j].second = 0;
				}
			}

			if (waitA.empty() && waitB.empty() && check(astate, N) && check(t, K)) break;
			
			time++;
			for (int i = 1; i <= N; i++) {
				if (astate[i].first > 0) astate[i].second++;
			}
			for (int j = 1; j <= M; j++) {
				if (bstate[j].first > 0) bstate[j].second++;
			}
		}

		// answer check
		for (int k = 1; k <= K; k++) {
			if (d[k].first == A && d[k].second == B) ans += k;
		}
		
		if (ans == 0) ans = -1;
		cout << "#" << tc << " " << ans << endl;
	}
	return 0;
}
