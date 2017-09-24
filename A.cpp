#include <iostream>
using namespace std;

int Answer;
int map[32];

int cnt(int size) {
	int count = 0;
	for (int i = 1; i <= size; i++) {
		if (map[i] == 1) count++;
	}
	return count;
}
void cp(int* a, int* b, int size) {
	for (int i = 1; i <= size; i++) {
		a[i] = b[i];
	}
}

void fill(int color, int index, int size) {
	map[index] = color;
	int left = index - 1;
	int right = index + 1;
	while (left > 0) {
		if (map[left] == 0 || map[left] == color) break;
		left--;
	}
	if (left != index-1 && map[left] != 0) {
		for (int k = left; k <= index - 1; k++) {
			map[k] = color;
		}
	}

	while (right <= size) {
		if (map[right] == 0 || map[right] == color) break;
		right++;
	}
	if (right != index + 1 && map[right] != 0) {
		for (int k = right; k >= index + 1; k--) {
			map[k] = color;
		}
	}
	for (int i = 1; i <= size; i++) {
		cout << map[i] << " ";
	}
	cout << endl;
}

int main(int argc, char** argv)
{
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		int N, ans = 0;
		int temp1[32], temp2[32], temp3[32];
		cin >> N;
		for (int i = 0; i < 30; i++) {
			map[i] = -1;
		}
		for (int i = 1; i <= N; i++) {
			cin >> map[i];
		}

		for (int x1 = 1; x1 <= N; x1++) {
			cp(temp1, map, N);
			if (map[x1] != 0) continue;
			fill(1, x1, N);
			for (int y1 = 1; y1 <= N; y1++) {
				if (map[y1] == 0) {
					fill(2, y1, N);
					break;
				}
			}
			for (int x2 = 1; x2 <= N; x2++) {
				cp(temp2, map, N);
				if (map[x2] != 0) continue;
				fill(1, x2, N);
				for (int y2 = 1; y2 <= N; y2++) {
					if (map[y2] == 0) {
						fill(2, y2, N);
						break;
					}
				}
				for (int x3 = 1; x3 <= N; x3++) {
					cp(temp3, map, N);
					if (map[x3] != 0) continue;
					fill(1, x3, N);
					for (int y3 = 1; y3 <= N; y3++) {
						if (map[y3] == 0) {
							fill(2, y3, N);
							break;
						}
					}
					int a = cnt(N);
					if (ans < a) ans = a;
					cp(map, temp3, N);
				}
				cp(map, temp2, N);
			}		
			cp(map, temp1, N);
		}
		cout << "#" << test_case << endl;
		cout << ans << endl;
	}
	return 0;
}
