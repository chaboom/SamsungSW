#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int map[10][10];

int select(int x, int y, int M, int C) {
	vector<int> selected(M,0);
	for (int j = y; j < y + M; j++) {
		selected.push_back(map[x][j]);
	}
	sort(selected.rbegin(), selected.rend());

	int sum1 = 0, sum2 = 0, max = 0;
	for (int k1 = 0; k1 < M; k1++) {
		for (int k2 = k1; k2 < M; k2++) {
			if (sum1 + selected[k2] > C) continue;
			sum1 += selected[k2];
			sum2 += selected[k2] * selected[k2];
		}
		if (max < sum2) max = sum2;
		sum1 = sum2 = 0;
	}
	return max;
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N, M, C, ans = 0;
		cin >> N >> M >> C;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		for (int x1 = 0; x1 < N; x1++) {
			for (int y1 = 0; y1 < N; y1++) {
				if (y1 + M > N) continue;
				int sum1 = select(x1, y1, M, C);
				
				for (int x2 = 0; x2 < N; x2++) {
					int y2;
					if (x2 != x1) y2 = 0;
					else y2 = y1 + M;
					for (; y2 < N; y2++) {						
						if (y2 + M > N) continue;
						int sum2 = select(x2, y2, M, C);
						if (ans < sum1 + sum2) ans = sum1 + sum2;
					}
				}
			}
		}
		cout << "#" << tc << " " << ans << endl;
	}
	return 0;
}
