#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100+10;

int dp[maxn][maxn];
char A[maxn];

bool match(int a, int b){
  if (A[a] == '(')
    return A[b] ==')';
  return A[a] == '[' && A[b] == ']';
}

int cal(int a, int b){ //[a,b]
  if (b-a <= 0) return 0;
  if (dp[a][b] != -1) return dp[a][b];
  int ans = 0;
  for (int i=a; i<b; i++){
    ans = max(ans, cal(a, i) + cal(i+1, b));
  }
  ans = max(ans, cal(a+1, b-1) + (match(a, b) ? 2 : 0));
  return dp[a][b] = ans;
}

int main(){
  while (scanf("%s", A) != -1 && A[0] != 'e'){
    memset(dp, -1, sizeof(dp));
    printf("%d\n", cal(0, strlen(A)-1));
  }
  return 0;
}