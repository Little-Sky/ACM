#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100+10;
int num[maxn];
int n;

//fixed cost, cost that times left, cost that times right
int dp[maxn][maxn];

int cal(int x, int y){ //(x, y)
  if (dp[x][y]) return dp[x][y];
  if (x+1 == y) return 0;
  dp[x][y] = 1e9;
  for (int k=x+1; k<y; k++)
    dp[x][y] = min(dp[x][y], num[x] * num[k] * num[y] + cal(x, k) + cal(k, y));
  return dp[x][y];
}

int main(){
  scanf("%d", &n);
  // memset(dp1, -1, sizeof(dp1));
  for (int i=0; i<n; i++)
    scanf("%d", num+i);
  printf("%d\n", cal(0, n-1));
}