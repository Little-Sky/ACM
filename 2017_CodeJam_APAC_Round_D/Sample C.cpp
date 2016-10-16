#include <cstdio>
#include <map>
#include <vector>

using namespace std;

const int N = 4001;
const int mod = 1000000007;

map<vector<int>, int> c;
char s[N];
int dp[N];
int n, m;

inline void update(int &a, long long b) {
	a = (a + b) % mod;
}

int main() {
	int t, tt;
	scanf("%d", &t);
	for (tt = 1; tt <= t; tt++) {
		scanf("%d%d", &n, &m);
		c.clear();
		for (int i = 0; i < n; i++) {
			vector<int> a(26);
			scanf("%s", s);
			for (int j = 0; s[j] != '\0'; j++) a[s[j] - 'a']++;
			c[a]++;
		}
		printf("Case #%d:", tt);
		for (int i = 0; i < m; i++) {
			scanf("%s", s);
			int ls = strlen(s);
			dp[0] = 1;
			for (int j = 0; j < ls; j++) {
				dp[j + 1] = 0;
				vector<int> a(26);
				for (int k = 0; k < 20 && j - k >= 0; k++) {
					a[s[j - k] - 'a']++;
					map<vector<int>, int>::iterator it = c.find(a);
					if (it != c.end()) update(dp[j + 1], (long long)dp[j - k] * it->second);
				}
			}
			printf(" %d", dp[ls]);
		}
		printf("\n");
	}
	return 0;
}


// //D.cpp brute force 2^n
//
// #include <cstdio>
// // #include <algorithm>
// // using namespace std;
// const int maxn = 1000;
// const int INF = 1e9;
// // int l[maxn];
// // int r[maxn];
// // int p[maxn];
//
// struct band{
//   int l, r, p;
//   void read(){scanf("%d%d%d", &l, &r, &p);}
// }B[maxn];
// int n, m, len;
//
// bool operator < (band a, band b){
//   return a.p < b.p;
// }
//
// int sol(){
//   int min = INF;
//   for (int ch=0; ch<=(1<<n); ch++){
//     int l = 0, r = 0, p = 0;
//     for (int i=0; i<n; i++){
//       if (ch & (1<<i)){
//         l += B[i].l;
//         r += B[i].r;
//         p += B[i].p;
//       }
//     }
//     if (p < min && l <= len && r >= len)
//       min = p;
//   }
//   return min;
// }
//
// int main(){
//   int kase;
//   scanf("%d", &kase);
//   for (int k_i=1; k_i<=kase; k_i++){
//     scanf("%d%d%d", &n, &m, &len);
//     for (int i=0; i<n; i++){
//       B[i].read();
//     }
//     int min = sol();
//     if (min <= m)
//       printf("Case #%d: %d\n", k_i, min);
//     else
//       printf("Case #%d: IMPOSSIBLE\n", k_i);
//   }
//   return 0;
// }


// B.cpp brute force, 2^n
//
// #include <cstdio>
// #include <cstring>
// const int maxn = 110;
//
// int a[maxn][maxn];
//
// bool check(int m, int n){
//   for (int i=1; i<=m; i++){
//     for (int j=1; j<=n; j++){
//       if (a[i][j]){
//         if (a[i-1][j] && a[i+1][j])
//           return false;
//         if (a[i][j-1] && a[i][j+1])
//           return false;
//       }
//     }
//   }
//   return true;
// }
//
// int sol(int m, int n){
//   int max = 0;
//   for (int j=0; j<=(1<<(m*n)); j++){
//     memset(a, 0, sizeof(a));
//     int cnt = 0, x=1, y=1, i = j;
//     while (i!=0){
//       if (y == n+1){
//         y = 1; x++;
//       }
//       a[x][y] = i%2;
//       if (a[x][y]) cnt++;
//       i/=2;
//       y++;
//     }
//     if (cnt > max && check(m,n)){
//       max = cnt;
//       if (max == 8){
//         for (int i1=1; i1<=m; i1++){
//           for (int i2=1; i2<=n; i2++){
//             printf("%d ", a[i1][i2]);
//           }
//           putchar('\n');
//         }
//       }
//     }
//   }
//   return max;
// }
//
// int main(){
//   int kase, x, y;
//   scanf("%d", &kase);
//   for (int i=1; i<=kase; i++){
//     scanf("%d%d", &x, &y);
//     printf("Case #%d: %d\n", i, sol(x,y));
//   }
//   return 0;
// }