#include <iostream>
using namespace std;

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };
int N;
int map[101][101];

bool checkPosition(int x, int y) {
	if (x == 0 || x == N - 1 || y == 0 || y == N - 1) return false;
	else return true;
}

int changedir(int dir) {
	if (dir == 1) return 2;
	else if (dir == 2) return 1;
	else if (dir == 3) return 4;
	else if (dir == 4) return 3;
	else return 0;
}
class __Mimic {
public:
	int direction, x, y, capacity;
	__Mimic() {}
	__Mimic(int px, int py, int c, int d) {
		direction = d;
		x = px;
		y = py;
		capacity = c;
	}
	void move() {
		if (capacity == 0) { 
			x = 0; y = 0;
			direction = 0;
		}
		map[x][y]--;
		x += dx[direction];
		y += dy[direction];
		map[x][y]++;
	}
};

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int M, K, ans = 0;
		cin >> N >> M >> K;
		Mimic m[1000];
		// input
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				map[i][j] = 0;
			}
		}
		for (int i = 0; i < K; i++) {
			int px, py, c, d;
			cin >> px >> py >> c >> d;
			m[i] = Mimic(px, py, c, d);
			map[px][py]++;
		}

		// simulation
		while (M > 0) {
			for (int k = 0; k < K; k++) {
				m[k].move();
				if (checkPosition(m[k].x, m[k].y) == false) {
					m[k].direction = changedir(m[k].direction);
					m[k].capacity /= 2;
				}
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (map[i][j] < 2) continue;
					int sum = 0, max = 0, mindex;
					for (int k = 0; k < K; k++) {						
						if (m[k].x == i && m[k].y == j) {
							if (max < m[k].capacity) {
								max = m[k].capacity;
								mindex = k;
							}
							sum += m[k].capacity;
							m[k].capacity = 0;
						}						
					}
					m[mindex].capacity = sum;
					map[i][j] = 1;
				}
			}
			M--;			
		}

		// ans
		for (int k = 0; k < K; k++) {
			ans += m[k].capacity;
		}
		cout << "#" << tc << " " << ans << endl;

	}

	return 0;
}
