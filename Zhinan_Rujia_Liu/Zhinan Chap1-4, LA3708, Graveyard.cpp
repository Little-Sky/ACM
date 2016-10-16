#include <cstdio>
#include <cmath>

int main(){
  int n, m, i, j;
  double p, sum;
  while (scanf("%d%d", &n, &m) != -1){
    m += n;
    sum = 0;
    for (i=0; i<n; i++){
      p = (double) i / n * m;
      
      /*A trick for getting the distance to the nearest int*/
      sum += fabs((int)(p+0.5) - p);
      
    }
    sum *= 10000.0/m;
    printf("%lf\n", sum);
  }
  return 0;
}
