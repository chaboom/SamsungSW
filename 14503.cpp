#include <iostream>
#include <queue>
#include <set>
using namespace std;

int map[50][50];
bool check[50][50];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

int search(int r, int c, int d)
{
	int next = (d + 3) % 4; // 회전
	int back = (d + 2) % 4; // 후진방향

	for (int cnt = 0;cnt < 4;cnt++) {
		if (map[r + dx[next]][c + dy[next]] == 0 && check[r + dx[next]][c + dy[next]] == false) return next;// 다음 공간 찾음
		next = (next + 3) % 4;
	}
	if (map[r + dx[back]][c + dy[back]] != 1) return -1;// 후진신호
	else return 5; // 정지신호
}

int go(int r, int c, int d)
{
	check[r][c] = true;
	int back = (d + 2) % 4;
	int next = search(r, c, d);
	if (next == -1) go(r + dx[back], c + dy[back], d);
	else if (next == 5) return 0;
	else go(r + dx[next], c + dy[next], next);
}

int main()
{
	int N, M, ans = 0;
	int r, c, d;
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	go(r, c, d);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (check[i][j]) ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
