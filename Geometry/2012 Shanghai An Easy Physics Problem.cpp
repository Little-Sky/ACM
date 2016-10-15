#include <cstdio>
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

const double PI = acos(-1);

struct Point{
  double x, y;
  Point(double a=0, double b=0):x(a), y(b) { }
};

typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Point(A.x+B.x, A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Point(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Point(p*A.x, p*A.y); }

const double eps = 1e-10;
int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x < 0 ? -1 : 1;
}

bool operator == (const Point& a, const Point& b){
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double ACOS(double x){
  if (!dcmp(1-x)) x = 1;
  if (!dcmp(1+x)) x = -1;
  return acos(x);
}
double SQRT(double x){
  if (dcmp(x) < 0) x = 0;
  return sqrt(x);
}
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return SQRT(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle
double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}



//Circle
struct Circle {
  Point c;
  double r;
  Circle (Point c = Point(), double r=0): c(c), r(r) {}
};

struct Line {
  Vector v;
  Point p;
  Line(Vector v, Point p):v(v), p(p) {}
  Line(){v = Point(0,0), p = Point(0,0);} 
};

Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}

int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2){
  double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
  double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;
  double delta = f*f - 4*e*g;       //判别式
  if (dcmp(delta) < 0) return 0;    //相离
  if (dcmp(delta) == 0){
    t1 = t2 = - f / (2 * e);
    return 1;
  }
  //相交
  t1 = (-f - SQRT(delta)) / (2 * e);
  t2 = (-f + SQRT(delta)) / (2 * e);
  return 2;
}

Line L; 
Circle C;
Point P;

int main(){
  int kase;
  cin >> kase;
  for (int K = 1; K <= kase; K++){
    cin >> C.c.x >> C.c.y >> C.r;
    cin >> L.p.x >> L.p.y >> L.v.x >> L.v.y;
    cin >> P.x >> P.y;
    cout << "Case #" << K << ": ";
    bool hit = false;
    double t1 = 0, t2 = 0;
    int ans = getLineCircleIntersection(L, C, t1, t2); 
    // cout << t1 << " " << t2 << endl;
    if ((ans < 2 || (dcmp(t1)<=0 && dcmp(t2)<=0)) && dcmp(Angle(L.v, P-L.p)) == 0){
      hit = true;
    }else if (ans == 2 && (dcmp(t1)>=0 || dcmp(t2)>=0)){
// cout << "Here?\n";
      double t = (t1 >= 0 ? t1 : t2);
      Point onC = L.p + L.v * t;
      assert(!dcmp(Length(onC-C.c) - C.r));
      double r_angle = Angle(L.v, (Vector)(C.c-onC));
      Vector R; 
      if (dcmp(Cross(L.v, (Vector)(C.c-onC))) >=0){
        R = Rotate(L.v, 2*r_angle+PI);
      }else{
        R = Rotate(L.v, 3*PI-2*r_angle);
      }
      if (dcmp(Angle(P-onC, R)) == 0){
        // cout << "1\n";
        hit = true;
      }else if (dcmp(Angle(onC-P, L.p-P) - PI) == 0 || P  == onC){
        // cout << "2\n";
        hit = true;
      }
// cout << "hit is " << hit << endl;
    }
    // cout << "WTF\n";
    if (hit)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}