#include <cstdio>
#include <iostream>
#include <algorithm>
const int maxn = 1010;

struct node{
  int a, b;
}n[maxn];

bool operator < (node x, node y){
  return x.b > y.b;
}

int main(){
  int kase, cnt=1;
  while (scanf("%d", &kase) != -1 && kase){
    for (int i=0; i<kase; i++)
      scanf("%d%d", &n[i].a, &n[i].b);
    std::sort(n, n+kase);
    int min = 0, cur = 0;
    for (int i=0; i<kase; i++){
      cur += n[i].a;
      // std::cout << cur << " " << min << std::endl;
      min = std::max(min, cur + n[i].b);
    }
    printf("Case %d: %d\n", cnt++, min);
  }
  return 0;
}
