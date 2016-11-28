#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100;
int n, T;
int num[maxn], sum[maxn];
int dp[maxn][maxn];

int cal(int x, int y){
  if (dp[x][y]) return dp[x][y];
  if (x >= y) return 0;
  
  dp[x][y] = sum[y] - sum[x] + cal(x+1, y);  //process x now
  for (int k=x+1; k<=y; k++)
    dp[x][y] = min(dp[x][y], (k-x)*num[x] + cal(x+1, k) + cal(k+1, y) + (k+1-x)*(sum[y] - sum[k]));
  // printf("%d %d %d\n", x, y, dp[x][y]);
  return dp[x][y];
}

int main(){
  scanf("%d", &T);
  for (int kase=1; kase<=T; kase++){
    memset(sum, 0, sizeof(sum));
    memset(dp, 0, sizeof(dp));
    scanf("%d", &n);
    for (int i=0; i<n; i++)
      scanf("%d", &num[i]);
    sum[0] = num[0];
    for (int i=0; i<n; i++)
      sum[i] = sum[i-1] + num[i];
    printf("Case #%d: %d\n", kase, cal(0, n-1));
  }
}
