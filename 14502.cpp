#include <iostream>
#include <string>
#include <queue>
#include <set>
using namespace std;

int map[8][8];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0 };
int N, M, ans = 0;
void bfs() 
{
	int temp[8][8];
	queue<pair<int, int>> q;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			temp[i][j] = map[i][j];
			if (temp[i][j] == 2) q.push(make_pair(i, j));
		}
	}
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
				if (temp[nx][ny] == 0) {
					temp[nx][ny] = 2;
					q.push(make_pair(nx, ny));
				}
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (temp[i][j] == 0) cnt++;
		}
	}
	if (ans < cnt) ans = cnt;	
}
int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int x1 = 0; x1 < N; x1++) {
		for (int y1 = 0; y1 < M;y1++) {
			if (map[x1][y1] != 0) continue;
			for (int x2 = 0; x2 < N; x2++) {
				for (int y2 = 0; y2 < M;y2++) {
					if (map[x2][y2] != 0) continue;
					for (int x3 = 0; x3 < N; x3++) {
						for (int y3 = 0; y3 < M;y3++) {
							if (map[x3][y3] != 0) continue;
							
							set<pair<int, int>> s = { 
								make_pair(x1,y1),
								make_pair(x2,y2),
								make_pair(x3,y3)
							};							
							if (s.size() != 3) continue;
							
							map[x1][y1] = 1;
							map[x2][y2] = 1;
							map[x3][y3] = 1;
							bfs();
							map[x1][y1] = 0;
							map[x2][y2] = 0;
							map[x3][y3] = 0;
						}
					}
				}
			}
		}	
	}
	cout << ans;
	return 0;
}
