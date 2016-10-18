#include <cmath>
#include <cstdio>

struct Point{
  double x, y;
  Point(double a=0, double b=0): x(a), y(b) { }

  void read() { scanf("%lf%lf", &x, &y); }
};

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

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle
double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}

//妈蛋 懂不懂啥叫“逆时针”
Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}

//调用前要确保两条直线 P+vt 和 Q+wt 有唯一交点，当且仅当 Cross(v,w) 非0
Point GetLineIntersection (Point P, Vector v, Point Q, Vector w){
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P + v*t;
}

Point Get (Point a, Point b, Point c){
  Vector x = c-b;
  double m = Angle(a-b, x);
  x = Rotate (x, m/3);
  // printf("%lf, %lf, %lf\n", x.x, x.y, m);
      
  Vector y = b-c;
  double n = Angle (a-c, y);
  y = Rotate (y, -n/3);

  
  return GetLineIntersection (b, x, c, y);  
}
int main(){
  int kase;
  scanf("%d", &kase);
  while (kase--){
    Point a, b, c, d, e, f;
    a.read(); b.read(); c.read();
    d = Get(a, b, c);
    e = Get(b, c, a);
    f = Get(c, a, b);
    printf("%.6lf %.6lf ", d.x, d.y);
    printf("%.6lf %.6lf ", e.x, e.y);
    printf("%.6lf %.6lf\n", f.x, f.y);
  }
  return 0;
}