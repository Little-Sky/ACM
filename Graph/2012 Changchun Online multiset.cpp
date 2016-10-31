#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 100100;
multiset<int> S;
pair<int, int> A[maxn], B[maxn];
int main(){
  int T, n;
  scanf("%d", &T);
  while (T--){
    S.clear();
    scanf("%d", &n);
    int a, b;
    for (int i=0; i<2*n; i++){
      scanf("%d%d", &a, &b);
      if (i < n) A[i] = {a, b};
      else B[i-n] = {a, b};
    }
    sort(A, A+n);
    sort(B, B+n);
    multiset<int>::iterator itr;
    int ans = 0, i, j=0;
    for (i=0; i<n; i++){
      while (j<n && A[i].first >= B[j].first)
        S.insert(B[j++].second);
      if (S.size()){
        itr = S.upper_bound(A[i].second);
        if (itr != S.begin()){
          itr--;
          S.erase(itr);
          ans++;
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
