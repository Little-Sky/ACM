typedef vector<Point> Polygon;

//转角法，可处理凸，凹，顺，逆甚至自交多边形；
int isPointInPolygon (Point p, Point* poly, int n){
  int wn = 0; //winding number
  for (int i=0; i<n; i++){
    if (OnSegment (p, poly[i], poly[(i+1)%n])) return -1;  //边界上
    int k = dcmp (Cross (poly[(i+1)%n]-poly[i], p-poly[i]));
    int d1 = dcmp (poly[i].y - p.y);
    int d2 = dcmp (poly[(i+1)%n].y - p.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;    //由下到上穿过水平向右射线
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;    //由上到下穿过水平向右射线
  }
  if (wn != 0) return 1; //内部
  return 0;              //外部
}

// 过两点p1, p2的直线一般方程ax+by+c=0 (x2-x1)(y-y1) = (y2-y1)(x-x1)
void getLineGeneralEquation(Point p1, Point p2, double& a, double& b, double& c){
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = p2.x * p1.y - p1.x * p2.y;
}

// 点集凸包 O(nlogn)
// 注意：函数执行完之后输入点的顺序被破坏
// 如果不希望在凸包的边上有输入点，把两个 <= 改成<
int ConvexHull(Point* p, int& n, Point* ch){
  sort(p, p+n);
  n = unique(p, p+n) - p; //To use vector: p.erase(unique(p.begin(), p.end()), p.end());
  int m = 0;
  for (int i=0; i<n; i++){
    while (m > 1 && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for (int i=n-2; i>=0; i--){
    while (m > k && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
    ch[m++] = p[i];
  }
  if (n > 1) m--;
  //To use vector: ch.resize(m);  !!!
  return m; //number of points on convex hull
}

int Dist2(const Point& A, const Point& B) {
  return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

// 旋转卡壳(Rotating Calipers): O(n)
// 返回点集直径  的  平方
// p 是多面体，ch是空array，用来存convex hull
int Diameter2(Point* p, int n, Point* ch) {
  int m = ConvexHull(p, n, ch); //m is size of ch
  if(m == 1) return 0;
  if(m == 2) return Dist2(ch[0], ch[1]);
  ch[m+1] = ch[0]; // 免得取模
  int ans = 0;
  for(int u = 0, v = 1; u < m; u++) {
    //u为起点，v是终点; u->u+1与v->v+1转角>=PI是判定对踵点；平行时需特判
    for(;;) {
      int diff = Cross(ch[u+1]-ch[u], ch[v+1]-ch[v]);
      if(diff <= 0) {
        ans = max(ans, Dist2(ch[u], ch[v]));
        if(diff == 0) ans = max(ans, Dist2(ch[u], ch[v+1]));
        break;
      }
      v = (v + 1) % m;
    }
  }
  return ans;
}
