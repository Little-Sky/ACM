#include <cstdio>
#include <cstring>
const int maxn = 110;

// int a[maxn][maxn];

// int sol(int m, int n){
//   // memset(a, 0, sizeof(a));
//   int cnt = 0;
//   for (int i=0; i<m; i++){
//     int i1 = i; j1 =j;
//     for (int j=0; j<n; j++){
//       while (j)
//       // if (!a[i][j]){
//       //   a[i][j] = 1;
//       //   cnt++;
//       //   if (a[i-1][j] == 1)
//       //     a[i+1][j] = -1; //not available
//       //   if (a[i][j-1] == 1)
//       //     a[i][j+1] = -1;
//       // }
//     }
//   }
//   return cnt;
// }

int sol(int m, int n){
  int cnt = 0;
  for (int i=0; i<m; i++){
    for (int j=0; j<n; j++)
      if ((i+j)%3 != 2)
        cnt ++;
  }
  int alter = (m/3+(m%3==2?1:0))*(n/3+(n%3==2?1:0))*4;
  if (alter > cnt)
    cnt = alter;
  return cnt;
}

int main(){
  int kase, x, y;
  scanf("%d", &kase);
  for (int i=1; i<=kase; i++){
    scanf("%d%d", &x, &y);
    printf("Case #%d: %d\n", i, sol(x,y));
  }
  return 0;
}