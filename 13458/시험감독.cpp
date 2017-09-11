#시험감독

using namespace std;
int main()
{ 
    int N, temp; 
    vector<int> A; 
    int B, C; 
    unsigned long long int ans = 0;
    cin >> N; 
   for (int i = 0; i < N; i++) 
   {  
    cin >> temp;  A.push_back(temp); 
   } 
   cin >> B >> C;

   for (int i = 0; i < N; i++)
   {  
     if (A[i] != 0) ans++; 
     A[i] = A[i] - B;  
     if (A[i] <= 0) A[i] = -1;  
     if ((A[i] / C) >= 1) ans += A[i] / C;  
     if ((A[i] % C) > 0) ans++; 
   }
     A.clear();
     cout << ans;
     return 0;
 }
