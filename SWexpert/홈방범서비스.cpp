#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<queue>
using namespace std;

int map[21][21];
bool checked[21][21];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
int N, M, ans;

void bfs(queue<pair<int, int> > q, int level, int count) {
	if (q.empty()) return;
	queue<pair<int, int> > nq;

	while (!q.empty()) {
		// 현재 queue count
		int x = q.front().first;
		int y = q.front().second;
		checked[x][y] = true;
		if (map[x][y] == 1) count++;
		q.pop();

		// 다음 level queue 생성
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];

			if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
				if (checked[nx][ny] == false) {
					checked[nx][ny] = true;
					nq.push(make_pair(nx, ny));
				}
			}
		}

	}
	int price = (level * level) + ((level-1) * (level-1));
	int benefit = (count * M) - price;

	if (benefit >= 0 && ans < count) ans = count;

	bfs(nq, ++level, count);
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int total = 0;
		ans = 0;
		cin >> N >> M;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) total++;
			}
		}
		if (total == N*N) {
			cout << "#" << tc << " " << total << endl; 
			break;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				queue<pair<int, int> > q;
				q.push(make_pair(i, j));
				bfs(q, 1, 0);

				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						checked[i][j] = false;
					}
				}
			}
			if (ans == total) break;
		}
		cout << "#" << tc << " " << ans << endl;
	}
	return 0;
}
