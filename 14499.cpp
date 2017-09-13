#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int C[6];
int posx, posy;
int map[20][20];

int roll(int flag) 
{	
	int temp = C[5];
	if (flag == 1){
		if (map[posx][posy + 1] < 0 || posy + 1>19) return -1;
		C[5] = C[2];
		C[2] = C[0];
		C[0] = C[1];
		C[1] = temp;		
		posy++;
	}
	if (flag == 2){
		if (map[posx][posy - 1] < 0 || posy - 1<0) return -1;
		C[5] = C[1];
		C[1] = C[0];
		C[0] = C[2];
		C[2] = temp;		
		posy--;
	}
	if (flag == 3){
		if (map[posx - 1][posy] < 0 || posx - 1 <0) return -1;
		C[5] = C[4];
		C[4] = C[0];
		C[0] = C[3];
		C[3] = temp;		
		posx--;
	}
	if (flag == 4){
		if (map[posx + 1][posy] < 0 || posx+1 >19) return -1;
		C[5] = C[3];
		C[3] = C[0];
		C[0] = C[4];
		C[4] = temp;		
		posx++;
	}
	if (map[posx][posy] == 0) map[posx][posy] = C[5];
	else if (map[posx][posy] != 0) {
		C[5] = map[posx][posy];
		map[posx][posy] = 0;
	}
	return 1;
}
int main()
{
	int N, M, K, temp;
	vector<int> Ki;
	memset(map, -1, sizeof(map));
	cin >> N >> M >> posx >> posy >> K;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++){
			cin >> map[i][j];
		}		
	}
	for (int i = 0; i < K; i++) {
		cin >> temp;
		Ki.push_back(temp);
	}
	
	for (int i = 0;i < K; i++)	{
		if (roll(Ki[i]) < 0) continue;	
		cout << C[0] << endl;
	}
	return 0;
}
