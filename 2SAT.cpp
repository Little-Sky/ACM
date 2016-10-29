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
  //for (x=xval) -> (y=yval) relation, use the commented version
  void add_clause(int x, int xval, int y, int yval){
    x = x*2 + xval;
    y = y*2 + yval;
    G[x^1].push_back(y); //G[x].push_back(y);
    G[y^1].push_back(x); //G[y^1].push_back(x^1);
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