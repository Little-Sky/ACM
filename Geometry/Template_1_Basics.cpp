#include <cmath>

struct Point{
  double x, y;
  Point(double a=0, double b=0): x(a), y(b) { }

  void read() { scanf("%lf%lf", &x, &y); }
};

inline Point get_point(){
  double x, y;
  cin >> x >> y;
  return Point(x, y);
}

typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Point(A.x+B.x, A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Point(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Point(p*A.x, p*A.y); }
Vector operator / (Vector A, double p) { return Point(A.x/p, A.y/p); }

bool operator < (const Point& a, const Point& b){
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

const double eps = 1e-10;
int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x<0 ? -1 : 1;
}

bool operator == (const Point& a, const Point& b){
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

//turning angle: [0, 2*PI)
double angle = atan2(y, x);

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle
double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}

double ACOS(double x){
  if (!dcmp(1-x)) x = 1;
  if (!dcmp(1+x)) x = -1;
  return acos(x); //loss precision significantly (14->7, 8->5 and so on). Avoid if possible!
}
double SQRT(double x){
  if (dcmp(x) < 0) x = 0;
  return sqrt(x);
}

double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }
//signed area; obey right-hand rule -> cross > 0

//逆时针转角
Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}

//单位法向量, make sure |A| != 0 before called
Vector Normal (Vector A) {
  double L = Length(A);
  return Vector(-A.y/L, A.x/L);
}

//过两点线参数方程: A+(B-A)*t; 直线: any t; 射线: t>0; 线段: t in [0,1];

//调用前要确保两条直线 P+vt 和 Q+wt 有唯一交点，当且仅当 Cross(v,w) 非0
Point GetLineIntersection (Point P, Vector v, Point Q, Vector w){
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P + v*t;
}

double DistanceToLine (Point P, Point A, Point B){
  Vector v1 = B - A, v2 = P - A;
  return fabs(Cross(v1, v2)) / Length(v1);  //不取绝对值得到的是有向距离
}

double DistanceToSegment (Point P, Point A, Point B){
  if (A == B) return Length(P-A);
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return fabs(Cross(v1, v2)) / Length(v1);
}

Point GetLineProjection (Point P, Point A, Point B){
  Vector v = B - A;
  return A + v * (Dot(v, P-A) / Dot(v, v));
}

//判断两线段有无交点（交点不可以在线段端点）
bool SegmentProperIntersection (Point a1, Point a2, Point b1, Point b2){
  double c1 = Cross (a2-a1, b1-a1), c2 = Cross (a2-a1, b2-a1),
         c3 = Cross (b2-b1, a1-b1), c4 = Cross (b2-b1, a2-b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
//判断某点 P 是否在另一线段 a1-a2 上（端点在另一个线段上）
bool OnSegment(Point P, Point a1, Point a2){
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
bool OnLine(Point A, Vector V, Point B){ //whether B on A + t*V
  return dcmp(Cross(V, B-A)) == 0;
}

//多边形的有向面积
double PolygonArea (Point* p, int n){
  double area = 0;
  for (int i = 1; i < n-1; i++)//用 p[0] 划分省去 i=n-1 的特殊处理 (下一个点p[n]其实是p[0])
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}

Euler Formula: For a plane, Vertex 顶点数 + Face 面数 - Edge 边数 = 2;

struct Line {
  Vector v;
  Point p;
  Line(Vector v, Point p):v(v), p(p) {}
  Line(){v = Point(0,0), p = Point(0,0);} 
};
