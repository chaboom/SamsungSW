#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int map[500][500];
int visit[500][500];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int go(int i, int j)
{
	int sum = map[i][j];
	int second = 0;
	visit[i][j] = 1;
	for (int s = 0; s < 3; s++){
		int max = 0, dir = -1;
		for (int k = 0; k < 4; k++) { // 4방향 check
			if (s == 1) second = max;
			if ((map[i + dy[k]][j + dx[k]] < 0) || (visit[i + dy[k]][j + dx[k]] == 1)) continue;
			if (max < map[i + dy[k]][j + dx[k]]) {				
				max = map[i + dy[k]][j + dx[k]];				
				dir = k;
			}
		}
		if (s == 2 && second > max) max = second;
		sum += max;
		i += dy[dir];
		j += dx[dir];
		visit[i][j] = 1;
	}
	return sum;
}

int main()
{
	int N, M;
	int ans = 0;
	memset(map, -1, sizeof(map));
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[500][500] = {0};
			int sum = go(i, j);
			if (ans < sum) ans = sum;
		}
	}
	cout << ans << endl;
	return 0;
}

