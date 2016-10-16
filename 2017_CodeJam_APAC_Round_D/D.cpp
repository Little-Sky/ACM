#include <cstdio>
// #include <algorithm>
// using namespace std;
const int maxn = 1000+10;
const int INF = 1e9;
int l[maxn];
int r[maxn];
int p[maxn];
// read(){scanf("%d%d%d", &l, &r, &p);}
int n, m, len;

bool operator < (band a, band b){
  return a.p < b.p;
}

const int maxn2 = 10000+10;
int dl[maxn2][maxn2];
int dp[maxn2]; 
int sol(){
  memset(dl, 0, sizeof(dl));
  memset(dp, 0, sizeof(dp));
  for (int i=0; i<n; i++){
    for (int j=n-1; j>=0; j--){
      if (dl[j][0] && j+l < n && dl[j+l])
    }
    for (int i=0; i<n; i++){
      if (ch & (1<<i)){
        l += B[i].l;
        r += B[i].r;
        p += B[i].p;
      }
    }
    if (p < min && l <= len && r >= len)
      min = p;
  }
  return min;
}

int main(){
  int kase;
  scanf("%d", &kase);
  for (int k_i=1; k_i<=kase; k_i++){
    scanf("%d%d%d", &n, &m, &len);
    for (int i=0; i<n; i++)
      scanf("%d%d%d", l+i, r+i, p+i);
    int min = sol();
    if (min <= m)
      printf("Case #%d: %d\n", k_i, min);
    else
      printf("Case #%d: IMPOSSIBLE\n", k_i);
  }
  return 0;
}