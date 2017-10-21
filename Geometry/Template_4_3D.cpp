struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
  void read(){ scanf("%llf%llf%llf", &x, &y, &z); }
};

typedef Point3 Vector3;

Vector3 operator + (Vector3 A, Vector3 B) { 
  return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); 
}
Vector3 operator - (Point3 A, Point3 B) { 
  return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); 
}
Vector3 operator * (Vector3 A, double p) { 
  return Vector3(A.x*p, A.y*p, A.z*p); 
}
Vector3 operator / (Vector3 A, double p) {
  return Vector3(A.x/p, A.y/p, A.z/p); 
}

double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector3& A, const Vector3& B) { return ACOS(Dot(A, B) / Length(A) / Length(B)); }
Vector3 Cross(const Vector3& A, const Vector3& B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
double Area2(const Point3& A, const Point3& B, const Point3& C) { return Length(Cross(B-A, C-A)); }
double Volume6(Point3 A, Point3 B, Point3 C, Point3 D) { 
  return Dot(D-A, Cross(B-A, C-A)); 
}

// 四面体的重心
Point3 Centroid(Point3 A, Point3 B, Point3 C, Point3 D) {
  return (A + B + C + D)/4.0; 
}

// 点p到平面p0-n的距离。n必须为单位向量
double DistanceToPlane(Point3 p, Point3 p0, Vector3 n) {
  return fabs(Dot(p-p0, n)); // 如果不取绝对值，得到的是有向距离
}
// 点p在平面p0-n上的投影。n必须为单位向量
Point3 GetPlaneProjection(Point3 p, Point3 p0, Vector3 n) {
  return p - n*Dot(p-p0, n);
}
//直线p1-p2与平面p0-n的交点，需保证线面不平行 (Dot(n, p2-p1) != 0)。
Point3 LinePlaneIntersection(Point3 p1, Point3 p2, Point3 p0, Vector3 n){
    vector3 = p2-p1;
    double t = (Dot(n, p0-p1) / Dot(n, p2-p1));
    return p1 + v*t; //如果是线段 判断t是否在0~1之间
}
//点P到直线AB的距离
double DistanceToLine( Point3& P, Point3& A, Point3& B) {
  Vector3 v1 = B - A, v2 = P - A;
  return Length(Cross(v1, v2)) / Length(v1);
}
//点到线段的距离
double DistanceToSeg(Point3 p, Point3 a, Point3 b){
  if(a == b) return Length(p-a);
  Vector3 v1 = b-a, v2 = p-a, v3 = p-b;
  if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return Length(Cross(v1, v2)) / Length(v1);  
}
//求异面直线 p1+s*u与p2+t*v的公垂线对应的s 如果平行|重合，返回false
bool LineDistance3D(Point3 p1, Vector3 u, Point3 p2, Vector3 v, double& s){
  double b = Dot(u, u) * Dot(v, v) - Dot(u, v) * Dot(u, v);
  if(dcmp(b) == 0) return false;
  double a = Dot(u, v) * Dot(v, p1-p2) - Dot(v, v) * Dot(u, p1-p2);
  s = a/b;
  return true;
}

// 点在三角形P0, P1, P2中
bool PointInTri(const Point3& P, const Point3& P0, const Point3& P1, const Point3& P2) {
  double area1 = Area2(P, P0, P1);
  double area2 = Area2(P, P1, P2);
  double area3 = Area2(P, P2, P0);
  return dcmp(area1 + area2 + area3 - Area2(P0, P1, P2)) == 0;
}

// 三角形P0P1P2是否和线段AB相交
bool TriSegIntersection(Point3& P0, Point3& P1, Point3& P2, Point3& A, Point3& B, Point3& P) {
  Vector3 n = Cross(P1-P0, P2-P0);
  if(dcmp(Dot(n, B-A)) == 0) return false; // 线段A-B和平面P0P1P2平行或共面
  else { // 平面A和直线P1-P2有惟一交点
    double t = Dot(n, P0-A) / Dot(n, B-A);
    if(dcmp(t) < 0 || dcmp(t-1) > 0) return false; // 不在线段AB上
    P = A + (B-A)*t; // 交点
    return PointInTri(P, P0, P1, P2);
  }
}

bool TriTriIntersection(Point3* T1, Point3* T2) {
  Point3 P;
  for(int i = 0; i < 3; i++) {
    if(TriSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i+1)%3], P)) return true;  
    if(TriSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i+1)%3], P)) return true;  
  }
  return false;
}

//空间两直线上最近点对 返回最近距离 点对保存在ans1 ans2中
double LineLineDistance(Point3 a1, Point3 b1, Point3 a2, Point3 b2, double& ans1, double& ans2){
  Vector3 v1 = (a1-b1), v2 = (a2-b2);
  Vector3 N = Cross(v1, v2);
  Vector3 ab = (a1-a2);
  double ans = Dot(N, ab) / Length(N);
  Point3 p1 = a1, p2 = a2;
  Vector3 d1 = b1-a1, d2 = b2-a2;
  double t1, t2;
  t1 = Dot((Cross(p2-p1, d2)), Cross(d1, d2));
  t2 = Dot((Cross(p2-p1, d1)), Cross(d1, d2));
  double dd = Length((Cross(d1, d2)));
  t1 /= dd*dd;
  t2 /= dd*dd;
  ans1 = (a1 + (b1-a1)*t1);
  ans2 = (a2 + (b2-a2)*t2);
  return fabs(ans);
}

// 判断P是否在凸四边形ABCD（顺时针或逆时针）中，并且到四条边的距离都至少为mindist。保证P, A, B, C, D共面
bool InsideWithMinDistance(Point3& P, Point3& A, Point3& B, Point3& C, Point3& D, double mindist) {
  if (!PointInTri(P, A, B, C)) return false;
  if (!PointInTri(P, C, D, A)) return false;
  if (DistanceToLine(P, A, B) < mindist) return false;
  if (DistanceToLine(P, B, C) < mindist) return false;
  if (DistanceToLine(P, C, D) < mindist) return false;
  if (DistanceToLine(P, D, A) < mindist) return false;
  return true;
}

//加干扰
double rand01() { return rand() / (double)RAND_MAX; }
double randeps() { return (rand01() - 0.5) * eps; }
Point3 add_noise(Point3& p) {
  return Point3(p.x + randeps(), p.y + randeps(), p.z + randeps());
}

//Unchecked!
struct Face {
  int v[3];
  Face(int a, int b, int c) { v[0] = a; v[1] = b; v[2] = c; }
  Vector3 Normal(const vector<Point3>& P) const {
    Vector3 v1 = P[v[1]]-P[v[0]], v2 = P[v[2]]-P[v[0]];
    double len = Length(v1) * Length(v2);
    return Cross(v1, v2) / len;
  }
  // f是否能看见P[i]
  int CanSee(const vector<Point3>& P, int i) const {
    return Dot(P[i]-P[v[0]], Normal(P)) > 0;
  }
};

// 增量法求三维凸包
int vis[maxn][maxn];  //maxn >= n
vector<Face> CH3D(Point3* P, int n) {
  vector<Face> cur;
  cur.push_back(Face(0, 1, 2)); // 由于已经进行扰动，前三个点不共线
  cur.push_back(Face(2, 1, 0));
  for(int i = 3; i < n; i++) {
    vector<Face> next;
    // 计算每条边的“左面”的可见性
    for(int j = 0; j < cur.size(); j++) {
      Face& f = cur[j];
      int res = f.CanSee(P, i);
      if(!res) next.push_back(f);
      for(int k = 0; k < 3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
    }
    for(int j = 0; j < cur.size(); j++)
      for(int k = 0; k < 3; k++) {
        int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
        if(vis[a][b] != vis[b][a] && vis[a][b]) // (a,b)是分界线，左边对P[i]可见
          next.push_back(Face(a, b, i));
      }
    cur = next;
  }
  return cur;
}

struct ConvexPolyhedron {
  int n;
  vector<Point3> P, P2;
  vector<Face> faces;

  bool read() {
    if(scanf("%d", &n) != 1) return false;
    P.resize(n);
    P2.resize(n);
    for(int i = 0; i < n; i++) { P[i] = read_point3(); P2[i] = add_noise(P[i]); }
    faces = CH3D(P2);
    return true;
  }
  //重心
  Point3 centroid() {
    Point3 C = P[0];
    double totv = 0;
    Point3 tot(0,0,0);
    for(int i = 0; i < faces.size(); i++) {
      Point3 p1 = P[faces[i].v[0]], p2 = P[faces[i].v[1]], p3 = P[faces[i].v[2]];
      double v = -Volume6(p1, p2, p3, C);
      totv += v;
      tot = tot + Centroid(p1, p2, p3, C)*v;
    }
    return tot / totv;
  }
  //C 到边最短
  double mindist(Point3 C) {
    double ans = 1e30;
    for(int i = 0; i < faces.size(); i++) {
      Point3 p1 = P[faces[i].v[0]], p2 = P[faces[i].v[1]], p3 = P[faces[i].v[2]];
      ans = min(ans, fabs(-Volume6(p1, p2, p3, C) / Area2(p1, p2, p3)));
    }
    return ans;
  }
};

