#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 10010;

struct TwoSAT{
  int n;
  vector<int> G[maxn*2];
  bool mark[maxn*2];
  int S[maxn*2], c; //cnt
  
  bool dfs(int x){
    if (mark[x^1]) return false;
    if (mark[x]) return true;
    mark[x] = true;
    S[c++] = x;
    for (int i=0; i<G[x].size(); i++)
      if (!dfs(G[x][i])) return false;
    return true;
  }
  
  void init(int n){
    this->n = n;
    for (int i=0; i<n*2; i++) G[i].clear();
    memset(mark, 0, sizeof(mark));
  }
  
  //x==xval or y==yval; val: 0-false, 1-true
  //x -> y
  void add_clause(int x, int xval, int y, int yval){
    x = x*2 + xval;
    y = y*2 + yval;
    G[x].push_back(y);
    G[y^1].push_back(x^1);
  }
  
  bool solve(){
    for(int i=0; i<n*2; i+=2)
      if (!mark[i] && !mark[i+1]){
        c = 0;
        if(!dfs(i)){
          while (c>0) mark[S[--c]] = false;
          if(!dfs(i+1)) return false;
        }
      }
    return true;
  }
}ts;

vector<int> V1, V2;
int main (){
  int T, m, n, a, b, c;
  scanf("%d", &T);
  for (int kase=1; kase<=T; kase++){
    scanf("%d%d", &m, &n);
    ts.init(m);
    V1.clear(); V2.clear();
    for (int i=0; i<m; i++){
      scanf("%d", &a);
      V1.push_back(a-1);
      V2.push_back(a%3);
    }
    for (int i=0; i<n; i++){
      scanf("%d%d%d", &a, &b, &c);
      a--; b--;
      if (c == 0){//equal
        if (V1[a] != V1[b]){
          ts.add_clause(a, 0, b, 1);
        }  
        if (V1[a] != V2[b]){
            ts.add_clause(a, 0, b, 0);
        }
        if (V2[a] != V1[b]){
          ts.add_clause(a, 1, b, 1);
        }  
        if (V2[a] != V2[b]){
            ts.add_clause(a, 1, b, 0);
        }
      }else if (c == 1){//not equal
        if (V1[a] == V1[b]){
          ts.add_clause(a, 0, b, 1);
        }  
        if (V1[a] == V2[b]){
            ts.add_clause(a, 0, b, 0);
        }
        if (V2[a] == V1[b]){
          ts.add_clause(a, 1, b, 1);
        }  
        if (V2[a] == V2[b]){
            ts.add_clause(a, 1, b, 0);
        }
      }
    }
    printf("Case #%d: %s\n", kase, ts.solve() ? "yes" : "no");
  }
  return 0;
}