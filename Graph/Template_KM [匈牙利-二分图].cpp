int nx, ny;
int G[maxn][maxn];
int cx[maxn], cy[maxn];
int visited[maxn];

int path(int u){
  int v;
  for (v=0; v<ny; v++){
    if (G[u][v] && !visited[v]){
      visited[v] = 1;
      if (cy[v] == -1 || path(cy[v])){
        cx[u] = v;
	cy[v] = u;
	return 1;
      }
    }
  }
  return 0;
}

int maxmatch (){
  int ans = 0;
  memset(cx, -1, sizeof(cx));	//-1: not paired
  memset(cy, -1, sizeof(cy));
  for (int i=0; i<=nx; i++){
    if (cx[i]==-1){
      memset(visited, 0, sizeof(visited));
      ans += path(i);
    }
  }
  return ans;
}
