#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
using namespace std;
const int maxn = 500 + 10;

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


int bs[maxn][maxn];
int main(){
    int n;
    while (scanf("%d", &n) != -1){
        bool ans = true;
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                scanf("%d", &bs[i][j]);
                if (i > j && bs[i][j] != bs[j][i]) ans = false;
                if (i==j && bs[i][j]) ans = false;
            }
        }
        
        /*
          Process 31 digits one by one to save memory!
          bitset is extremely slow! Avoid it.
        */
        
        for (int k=0; k<31 && ans; k++){
            ts.init(n);
            for (int i=0; i<n; i++){
                for (int j=i+1; j<n; j++){
                   // bitset<31> c(bs[i][j]);
                    int c = (bs[i][j] >> k) & 1;
                    if (i%2 && j%2){
                        if (c){
                            ts.add_clause(i, 0, j, 1);
                        }else{
                            ts.add_clause(i, 1, i, 0);
                            ts.add_clause(j, 1, j, 0);
                        }
                    }else if (i%2 == 0 && j%2 == 0){
                        if (c){
                            ts.add_clause(i, 0, i, 1);
                            ts.add_clause(j, 0, j, 1);
                        }else{
                            ts.add_clause(i, 1, j, 0);
                        }
                    }else{
                        if (c){
                            ts.add_clause(i, 0, j, 1);
                            ts.add_clause(i, 1, j, 0);
                        }else{
                            ts.add_clause(i, 0, j, 0);
                            ts.add_clause(i, 1, j, 1);
                        }
                    }
                }
            }
            if (!ts.solve()) {
                ans = false;
                break;
            }
       }
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}