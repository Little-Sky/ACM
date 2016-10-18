//Circle
struct Circle {
  Point o;
  double r;
  Point getPoint (double a){ //in rad
    return Point (o.x + cos(a)*r, o.y + sin(a)*r);
  }
  void read() { scanf("%lf%lf%lf", &o.x, &o.y, &r); }
};

//sol 并未清空，方便累计交点
int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol){
  double a = L.v.x, b = L.p.x - C.o.x, c = L.v.y, d = L.p.y - C.o.y;
  double e = a*a + c*c, f = 2*(a*b+c*d), g = b*b + d*d - C.r*C.r;
  double delta = f*f - 4*e*g;       //判别式
  if (dcmp(delta) < 0) return 0;    //相离
  if (dcmp(delta) == 0){
    t1 = t2 = -f/(2*e); sol.push_back(L.point(t1));
    return 1;
  }
  //相交
  t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(L.point(t1));
  t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(L.point(t2));
  return 2;
}

/*if (error of x is larger than 1e-8), 
then the acos error would be within 1e-3 (1.5e-5)*/
double ACOS(double x){
  if (fabs(1-x) < 1e-8) x = 1;
  if (fabs(1+x) < 1e-8) x = -1;
  return acos(x); //loss precision significantly (10->4, 8->3 and so on). Avoid if possible!
}

double angle(Vector v) { return atan2(v.y, v.x); }

int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol){
  double d = Length(C1.o - C2.o);
  if (dcmp(d) == 0){
    if (dcmp(C1.r - C2.r) == 0) return -1;  //重合
    return 0; //同心
  }
  if (dcmp(C1.r + C2.r - d) < 0) return 0;  //太远
  if (dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;  //大包小
  
  double a = angle (C2.o - C1.o); //向量C1C2的极角
  double da = ACOS((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d)); //余弦定理 解C1C2与C1P夹角
  Point p1 = C1.point(a-da), p2 = C1.point(a+da);
  
  sol.push_back(p1);
  if (p1 == p2) return 1;
  sol.push_back(p2);
  return 2;
}

//Template unchecked!
int getTangents(Point p, Circle C, Vector* v){ //切线向量
  Vector u = C.o - p;
  double dist = Length(u);
  if (dist < C.r) return 0;
  else if (dcmp(dist - C.r) == 0){  //p在圆上只有一条切线
    v[0] = Rotate(u, PI/2);
    return 1;
  }else{
    double ang = PI/2 - ACOS(C.r / dist);
    v[0] = Rotate(u, -ang);
    v[1] = Rotate(u, ang);
    return 2;
  }
}

//a[i], b[i] 分别是第i条切线在圆A和圆B上的切点; size: 4; 6 cases, return -1 to 4
int getTangents(Circle A, Circle B, Point* a, Point* b){
  int cnt = 0;
  // if (A.r < B.r) { swap(A, B); swap(a, b); }
  double d = Length(A.o-B.o);
  double rdiff = fabs(A.r - B.r);
  double rsum = A.r + B.r;
  if (dcmp(d-rdiff) < 0) return 0;  //内含
  
  double base = angle(B.o-A.o);
  if (dcmp(d) == 0 && dcmp(A.r-B.r) == 0) return -1;  //重合，无数条切线
  if (dcmp(d-rdiff) == 0){  //内切，1条切线
    a[cnt] = A.getPoint(base); b[cnt] = B.getPoint(base); cnt++;
    return 1;
  }
  //有外共切线
  double ang = ACOS( (A.r-B.r) / d );
  a[cnt] = A.getPoint(base+ang); b[cnt] = B.getPoint(base+ang); cnt++; 
  a[cnt] = A.getPoint(base-ang); b[cnt] = B.getPoint(base-ang); cnt++;
  if (dcmp(d-rsum) == 0){   //一条公切线
    a[cnt] = A.getPoint(base); b[cnt] = B.getPoint( PI + base); cnt++;
  }
  else if(dcmp(d-rsum) > 0){  //两条公切线
    double ang = acos((A.r + B.r) / d);
    a[cnt] = A.getPoint(base+ang); b[cnt] = B.getPoint( PI + base+ang); cnt++; 
    a[cnt] = A.getPoint(base-ang); b[cnt] = B.getPoint( PI + base-ang); cnt++;
  }
  return cnt;
}

