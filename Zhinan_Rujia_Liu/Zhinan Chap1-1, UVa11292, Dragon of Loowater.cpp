#include <cstdio>
#include <algorithm>
const int maxn = 20000 + 10;

int a[maxn];
int b[maxn];

int m, n;

int main(){
  while(scanf("%d%d", &n, &m) && (n && m)){
    int i,j;
    long long cost = 0;
    for (i=0; i<n; i++)
      scanf("%d", a+i);
    for (i=0; i<m; i++)
      scanf("%d", b+i);
    std::sort(a, a+n);
    std::sort(b, b+m);
    i = j = 0;
    while (i != n && j != m){
      if (b[j] >= a[i]){
        cost += b[j];
        i++;
      }
      j++;
    }
    if (i == n)
      printf("%lld\n", cost);
    else
      printf("Loowater is doomed!\n");
  }
  return 0;
}
