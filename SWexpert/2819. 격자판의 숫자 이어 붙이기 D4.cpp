#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// 0:Left 1:up 2:Right 3:Down
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
char map[4][4];
bool visit[4][4];
vector<string> findset;

void init() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			visit[i][j] = false;
		}
	}
}
bool check(string s) {
	for (int i = 0; i < findset.size(); i++) {
		if (findset[i] == s) return false;
	}
	return true;
}
void dfs(int x, int y, string selected) {
	if (selected.length() == 7) {
		//if (check(selected)) findset.push_back(selected);
		cout << x << y << selected << " ";
		return;
	}
	visit[x][y] = true;
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx >= 0 && ny >= 0 && nx < 4 && ny < 4) {
			if (!visit[nx][ny]) {
				selected += map[nx][ny];
				dfs(nx, ny, selected);
				visit[nx][ny] = false;
			}
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int ans = 0;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> map[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				init();
				cout << endl << "("<< i <<", "<< j <<")" << "start: " << ""+map[i][j] << endl;
				string start;
				dfs(i, j, start);
			}
		}
		for (int k = 0; k < findset.size(); k++) {
			cout << findset[k] << "  ";
		}
		cout << endl;
		ans = findset.size();
		cout << "#" << tc << " " << ans << endl;
	}
	return 0;
}
