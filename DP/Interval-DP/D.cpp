//10:27
#include <cstdio>
#include <cstring>
#include <stack>
typedef long long LL;
using namespace std;
const LL maxn = 1000;
const LL mod = 1e9+7;
LL pr[maxn], dp[maxn][maxn][3][3];
char A[maxn];

void cal_dp(LL x, LL y){
  if (y-x == 1){
    dp[x][y][0][1] = dp[x][y][0][2] = dp[x][y][1][0] = dp[x][y][2][0] = 1;
  }else{
    if (pr[x] == y){ // ( a )
      cal_dp(x+1, y-1);
      for (LL i=0; i<3; i++){
        for (LL j=0; j<3; j++){
          if (i*j || (!i && !j)) continue;
          for (LL p=0; p<3; p++){
            for (LL q=0; q<3; q++){
              if ((i==p && i) || (j==q && j)) continue;
              dp[x][y][i][j] += dp[x+1][y-1][p][q];
              dp[x][y][i][j] %= mod;
            }
          }
        }
      }
    }else{      // c = a b
      LL m = pr[x];
      cal_dp(x, m);
      cal_dp(m+1, y);
      for (LL i=0; i<3; i++){
        for (LL j=0; j<3; j++){
          for (LL p=0; p<3; p++){
            if ((j==p) && j) continue;
            for (LL q=0; q<3; q++){
              dp[x][y][i][q] += dp[x][m][i][j] * dp[m+1][y][p][q];
              dp[x][y][i][q] %= mod;
            }
          }
        }
      }
    }
  }
}

stack<LL> S;
void pre(LL n){
  for (LL i=0L; i<=n; i++){
    if (A[i] == '(')
      S.push(i);
    else{
      LL a = S.top(); S.pop();
      pr[a] = i;
      pr[i] = a;
    }
  }
}

int main(){
  scanf("%s", A);
  LL n = strlen(A);
  n--;
//  printf("%d\n", n);
  pre(n);
//  printf("finish pre\n");
  cal_dp(0, n);
//  printf("finish dp\n");
  LL ans = 0;
  for(LL i=0; i<3; i++)
    for(LL j=0; j<3; j++)
      ans += dp[0][n][i][j];
  printf("%lld\n", ans % mod);
}