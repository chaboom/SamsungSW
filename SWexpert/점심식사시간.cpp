#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int stairsize[3]; // 0번 배열 안씀
pair<int, int> stairloc[3];
pair<int, int> person[11]; // first: stair1-distance, second: stair2-distance

int calc(vector<int> stair, int num) {
	int totaltime = 0, in = 0, out = 0;
	queue<int> s;
	totaltime = stair[0] + 1;

	while (true) {
		while (!s.empty() && s.front() == totaltime) {
			s.pop();
			out++;
		}
		for (int k = in; k < stair.size(); k++) {
			if (totaltime >= (stair[k] + 1)) {
				if (s.size() < 3) {
					s.push(totaltime + stairsize[num]);
					in++;
				}
			}
		}		
		if (out == stair.size()) break;
		totaltime++;		
	}

	return totaltime;
}
int get_max(int pcnt, int pnum, string select) {
	string selected = select;
	if (selected.length() == pcnt) {
		vector<int> select1, select2;
		for (int k = 1; k <= pcnt; k++) {
			if (selected[k-1] == '1') select1.push_back(person[k].first);
			else select2.push_back(person[k].second);				
		}
		int s1 = 0, s2 = 0;
		if (select1.size()) {
			sort(select1.begin(), select1.end());
			s1 = calc(select1, 1);
		}
		if (select2.size()) {
			sort(select2.begin(), select2.end());
			s2 = calc(select2, 2);
		}
		
		int maxd = max(s1, s2);

		return maxd;
	}
	return min(get_max(pcnt, pnum + 1, selected + "1"), get_max(pcnt, pnum + 1, selected + "2"));
}

pair<int, int> get_distance(int i, int j) {
	int distance1 = abs(stairloc[1].first - i) + abs(stairloc[1].second - j);
	int distance2 = abs(stairloc[2].first - i) + abs(stairloc[2].second - j);
	return make_pair(distance1, distance2);
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int map[12][12];
		int N, ans = 0, pcnt = 0, scnt = 0;
		cin >> N;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> map[i][j];
				if (map[i][j] > 1) {
					stairsize[++scnt] = map[i][j];
					stairloc[scnt] = make_pair(i, j);
				}
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (map[i][j] == 1) {
					person[++pcnt] = get_distance(i, j);
				}
			}
		}
		ans = min(get_max(pcnt, 1, "1"), get_max(pcnt, 1, "2"));

		cout << "#" << tc << " " << ans << endl;
	}
	return 0;
}
