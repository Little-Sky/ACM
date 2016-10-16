#include <cstdio>
#include <algorithm>
const int maxn = 10000 + 10;

struct Ant{
  int p, id, d; //d  = -1: L; 0: Turning; 1: R;
  bool operator < (Ant x) const{
    return p < x.p;
  }
}before[maxn], after[maxn];

int order[maxn];

int main(){
  int kase, len, t, n;
  char buf[10];
  scanf("%d", &kase);
  for (int cnt = 1; cnt <= kase; cnt ++){
    printf("Case #%d:\n", cnt);
    scanf("%d%d%d", &len, &t, &n);
    // printf("%d%d%d are\n", len, t, n);
    for (int i=0; i<n; i++){
      scanf("%d %s", &before[i].p, buf);
      before[i].id = i;
      before[i].d = (buf[0] == 'R'? 1 : -1);
      after[i].p = before[i].p + t*before[i].d;
      after[i].d = before[i].d;
    }
    
    std::sort(before, before+n);
    for (int i=0; i<n; i++){
      order[before[i].id] = i;
    }
    
    std::sort(after, after+n);
    for (int i=1; i<n; i++){
      if (after[i].p == after[i-1].p)
        after[i].d = after[i-1].d = 0;
    }
    
    for (int i=0; i<n; i++){
      Ant& c = after[order[i]];
      if (c.p < 0 || c.p > len){
        printf("Fell off\n");
      }else{
        printf("%d ", c.p);
        if (!c.d){
          printf("Turning\n");
        }else if (c.d > 0){
          printf("R\n");
        }else{
          printf("L\n");
        }
      }
    }
    putchar('\n');
  }
  return 0;
}