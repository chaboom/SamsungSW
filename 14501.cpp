#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
int D[16];
int main()
{
	int N;
	vector<int> T;
	vector<int> P;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		T.push_back(temp1);
		P.push_back(temp2);
	}
	D[0] = 0;
	for (int i = 0; i < N; i++)
	{
		D[i + T[i]] = max(D[i + T[i]], D[i] + P[i]);
		D[i + 1] = max(D[i + 1], D[i]);
	}
	cout << D[N];
	return 0;
}
