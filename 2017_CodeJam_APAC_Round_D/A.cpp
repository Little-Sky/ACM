#include <cstdio>
#include <cstring>
#include <cmath>
const int maxn = 2010;
const double eps = 1e-8;

int dcmp(double a){
  if (fabs(a) < eps) return 0;
  return a < 0 ? -1 : 1;
}

long double a[maxn][maxn];

long double rec(int m, int n){
  if (m*n == 0){
    a[m][n] = 1;
  }else if (!dcmp(a[m][n])){
    // printf("get into %d %d\n", m, n-1);
    a[m][n] = rec(m, n-1) + (m-1 > n ? rec(m-1, n) : 0);
  }
  // printf("m is %d, n is %d, a[m][n] is %lf\n", m, n, a[m][n]);
  return a[m][n];
}

long double select(long double cur, int m, int n){
  if (n == 0)
    return cur;
  return select(cur*n/m, m-1, n-1);
}

int main(){
  int kase, x, y;
  scanf("%d", &kase);
  for (int i=1; i<=kase; i++){
    memset(a, 0, sizeof(a));
    scanf("%d%d", &x, &y);
    printf("Case #%d: %.8Lf\n", i, select(rec(x, y), x+y, x));
    // printf("%.8lf")
  }
  return 0;
}