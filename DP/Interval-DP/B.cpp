#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 200;
int color[maxn], n;
// vector<int> next[maxn];
int dp[maxn][maxn]; //already have ith cloth. how many more needed for interval i,j

int cal(int x, int y){// (x, y]
  if (dp[x][y] != -1){
    return dp[x][y];
  }else if (x == y){
    return dp[x][y] = 0;
  }else if (x+1 == y){
    return dp[x][y] = (color[y] == color[x] ? 0 : 1);
  }else{
    dp[x][y] = y - x;
    for (int i=x+1; i<y; i++){
      if (color[i] == color[x]){
        // printf("(%d %d) %d (%d %d), %d\n", x, i, cal(x,i), i, y, cal(i,y));
        dp[x][y] = min(dp[x][y], cal(x,i) + cal(i,y));
      }
    }
    if (color[x] == color[y])
      dp[x][y] = min(dp[x][y], cal(x, y-1));
    else
      dp[x][y] = min(dp[x][y], 1+cal(x+1, y));
    // printf("(x,y) %d %d %d\n", x, y, dp[x][y]);
    return dp[x][y];
  }
}

int main(){
  int T;
  scanf("%d", &T);
  for (int kase=1; kase<=T; kase++){
    scanf("%d", &n);
    for (int i=0; i<n; i++)
      scanf("%d", &color[i]);
    memset(dp, -1, sizeof(dp));
    printf("Case %d: %d\n", kase, 1+cal(0, n-1));
  }
  return 0;
}